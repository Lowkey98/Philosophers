/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayafdel <ayafdel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 19:55:03 by ayafdel           #+#    #+#             */
/*   Updated: 2022/03/05 13:21:13 by ayafdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

pthread_mutex_t	*lock_and_print(pthread_mutex_t *mutex, char *str, int arg_one, int arg_two)
{
		pthread_mutex_lock(mutex);
		printf(str, get_current_time_msec(arg_one), arg_two);
		pthread_mutex_unlock(mutex);
		return (mutex);
}

int     get_current_time_usec()
{
	struct timeval  tv;
	
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000000 + tv.tv_usec);
}

void	ft_usleep(int	period)
{
	int end_time;

	
	end_time = get_current_time_usec() + period;

	usleep(period - 2000);
	while(get_current_time_usec() < end_time)
	{
		
		// if (get_current_time_usec() > end_time)
		// 	return;
		usleep(500);
	}

}

int		pick_up_forks(t_philo *data)
{
	pthread_mutex_lock(data->left_fork);
	lock_and_print(data->print_mutex, "%d philo %d has taking left fork\n", data->t_zero, data->philo_id );
	pthread_mutex_lock(data->right_fork);
	lock_and_print(data->print_mutex, "%d philo %d has taking right fork\n", data->t_zero, data->philo_id );
	return (0);
}

int		put_down_forks(t_philo *data)
{
	pthread_mutex_unlock(data->left_fork);
	pthread_mutex_unlock(data->right_fork);
	return (0);
}
int		sleep_think(t_philo *data)
{
	lock_and_print(data->print_mutex, "%d philo %d sleeping\n", data->t_zero, data->philo_id );
	ft_usleep(data->argv_data->time_to_sleep * 1000);
	lock_and_print(data->print_mutex, "%d philo %d thinking\n", data->t_zero, data->philo_id );	
	return (0);
}
void *philo_routine(void *vargp)
{
	t_philo *data;

	data = vargp; 

	while(1)
	{
		pick_up_forks(data);
		data->last_ate = get_current_time_msec(data->t_zero);
		lock_and_print(data->print_mutex, "%d philo %d eating\n", data->t_zero, data->philo_id );
		ft_usleep(data->argv_data->time_to_eat * 1000);
		data->times_ate++;
		put_down_forks(data);
		sleep_think(data);

	}
	return NULL;
}



int		fetch_fork_data(pthread_mutex_t **forks, int n_philo)
{
	int i;

	i = 0;

	*forks = malloc(sizeof(pthread_mutex_t) * n_philo);
	if (*forks == NULL)
		return (1);
	while (i < n_philo)
	{
		if (pthread_mutex_init(&(*forks)[i], NULL) != 0)
		{
			free(*forks);
			return (1);
		}
		i++;
	}
	return (0);
}

int	fetch_philo_data(t_philo **philo_data, pthread_mutex_t **fork_list, t_argv *argv_data)
{
	int i;
	pthread_mutex_t *print_mutex;

	i = 0;
	print_mutex = malloc(sizeof(pthread_mutex_t));
	if (print_mutex == NULL)
	{
		return (1);
	}
	if (pthread_mutex_init(print_mutex, NULL) != 0)
	{
		free(print_mutex);
		return(1);
	}
	while (i <  argv_data->number_of_philo)
	{
		(*philo_data)[i].print_mutex = print_mutex;
		(*philo_data)[i].philo_id = i + 1;
		(*philo_data)[i].argv_data = argv_data;
		(*philo_data)[i].left_fork = &(*fork_list)[i];
		(*philo_data)[i].right_fork = &(*fork_list)[(i + 1) % argv_data->number_of_philo];
		i++;
	}
	return (0);
}

int     fetch_philos_data(t_philo **philo_data, char **argv, int argc)
{
	t_argv *argv_data;
	pthread_mutex_t *fork_list;
	int i;

	i = 0;
	if (args_error(argv, argc))
	{
		ft_putstr_fd("error argument", 2);
		return (1);
	}
	if (fetch_argv_data(&argv_data, argv) == 1)
		return (1);
	if (fetch_fork_data(&fork_list, argv_data->number_of_philo) == 1)
	{
		free(argv_data);
		return (1);
	}
	*philo_data = malloc(sizeof(t_philo )  * argv_data->number_of_philo);
	if (*philo_data == NULL)
	{
		free(*philo_data);
		free(argv_data);
		free(fork_list);
		return (1);
	}
	if (fetch_philo_data(philo_data, &fork_list, argv_data) == 1)
	{
		free(*philo_data);
		free(argv_data);
		free(fork_list);
		return (1);	
	}
	return (0);
}


void check_deaths(t_philo *philo_data, int t_zero)
{
	int i;
	int ate_flag;


	ate_flag = 0;
	i = 0;
	while(1)
	{
		while (i < philo_data->argv_data->number_of_philo)
		{
			if (get_current_time_msec(t_zero) - philo_data[i].last_ate > philo_data[i].argv_data->time_to_die) 
			{		
				pthread_mutex_lock(philo_data->print_mutex);
				printf("%d ms: philo %d DIED\n",get_current_time_msec(t_zero), philo_data[i].philo_id);
				return ;
			}
			if (philo_data->argv_data->number_of_eats != -1)
			{
				if (philo_data[i].times_ate < philo_data->argv_data->number_of_eats )
					ate_flag = 1;
			}
			
			i++;
						
		}
		if (ate_flag == 0 && philo_data->argv_data->number_of_eats != -1)
		{
			pthread_mutex_lock(philo_data->print_mutex);
			printf("%dms :EVERYONE ATE atleast %d times\n", get_current_time_msec(philo_data->t_zero), philo_data->argv_data->number_of_eats);
			return ;
		}
		ate_flag = 0;
		i = 0;
	}
}

int		create_philo_set(int i, t_philo *philo_data, int t_zero)
{
	pthread_t *thread_id_list;

	thread_id_list = malloc(sizeof(pthread_t) * philo_data->argv_data->number_of_philo);
	if (thread_id_list == NULL)
		return (1);
	while (i < philo_data->argv_data->number_of_philo)
	{
		philo_data[i].t_zero = t_zero;
		philo_data[i].times_ate = 0;		
		philo_data[i].last_ate = get_current_time_msec(t_zero);
		pthread_create(&thread_id_list[i], NULL, philo_routine, &philo_data[i]);
		// usleep(10000);
		i += 2;
	}
	return (0);
}

int	start_philos(t_philo *philo_data, int t_zero)
{
	int i;
	
	i = 0;
	// printf("--%d--\n", philo_data[i].argv_data->number_of_philo);
	if (create_philo_set(0, philo_data, t_zero) == 1)
		return (1);
	usleep(100); // 2
	if (create_philo_set(1, philo_data, t_zero) == 1)
		return (1);
	// i = 0;
	// while (i < philo_data->argv_data->number_of_philo)
	// {
	// 	pthread_join(thread_id_list[i], NULL);
	// 	i++;
	// }
	return (0);
}

void	detach_destroy_free(t_philo *philo_data)
{
	int i;
	int n;

	i = 0;
	n = philo_data->argv_data->number_of_philo;
	while (i < n)
	{
		
	}
}
int main(int argc, char **argv)
{

	t_philo *philo_data;
	int t_zero;

	t_zero = get_t_zero();
	if (fetch_philos_data(&philo_data, argv, argc) == 1)
		return (1);
	// printf("test : %d\n", philo_data[0].argv_data->number_of_philo);
	if (start_philos(philo_data, t_zero) == 1)
	{
		// FREE ALL PHILO DATA
		return (1);
	}
	check_deaths(philo_data, t_zero);
	detach_destroy_free(philo_data);
	
	return (0);
}
