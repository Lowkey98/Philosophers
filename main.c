/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayafdel <ayafdel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 19:55:03 by ayafdel           #+#    #+#             */
/*   Updated: 2022/02/28 11:39:38 by ayafdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


void *func(void *vargp)
{
	printf("-------------\n");
	t_philo *data;

	data = vargp; 

	// printf("times ate %d\n", data->argv_data->number_of_eats);
	while(1)
	{
		pthread_mutex_lock(data->left_fork);
		printf("%dms:philo %d has taking left fork\n",get_current_time_msec(data->t_zero),data->philo_id);
		pthread_mutex_lock(data->right_fork);
		printf("%dms:philo %d has taking right fork\n",get_current_time_msec(data->t_zero),data->philo_id);
		printf("%dms:philo %d eating\n",get_current_time_msec(data->t_zero),data->philo_id);
		usleep(data->argv_data->time_to_eat * 1000);
		pthread_mutex_unlock(data->left_fork);
		pthread_mutex_unlock(data->right_fork);
		data->last_ate = get_current_time_msec(data->t_zero);
		printf("%dms:philo %d sleeping\n", get_current_time_msec(data->t_zero),data->philo_id);
		usleep(data->argv_data->time_to_sleep * 1000);
		printf("%dms:philo %d thinking\n",get_current_time_msec(data->t_zero),data->philo_id);
	}
	
	// exit(0);
	
	// printf("value =%d\n", a);
	return NULL;
}



int		fetch_fork_data(pthread_mutex_t **forks, int n_philo)
{
	int i;

	i = 0;

	*forks = malloc(sizeof(pthread_mutex_t) * n_philo);
	while (i < n_philo)
	{
		pthread_mutex_init(&(*forks)[i], NULL);
		i++;
	}
	return (0);
}

int     fetch_philo_data(t_philo **philo_data, char **argv, int argc)
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
		return (1);
	*philo_data = malloc(sizeof(t_philo )  * argv_data->number_of_philo);
	while (i <  argv_data->number_of_philo)
	{

		(*philo_data)[i].left_fork = &fork_list[i];
		(*philo_data)[i].philo_id = i + 1;
		(*philo_data)[i].right_fork = &fork_list[(i + 1) % argv_data->number_of_philo];
		(*philo_data)[i].argv_data = argv_data;
		i++;
	}
	return (0);
}

void check_deaths(t_philo *philo_data, int t_zero)
{
	int i;

	i = 0;
	while(1)
	{
		while (i < philo_data->argv_data->number_of_philo)
		{
			if (get_current_time_msec(t_zero) - philo_data[i].last_ate > philo_data[i].argv_data->time_to_die) 
			{
				printf("%d ms: philo %d DIED\n",get_current_time_msec(t_zero), philo_data[i].philo_id);
				return ;
			}
			i++;			
		}
		i = 0;
	}
}

void	create_philo_set(int i, t_philo *philo_data, int t_zero)
{
	pthread_t *thread_id_list;

	thread_id_list = malloc(sizeof(pthread_t) * philo_data->argv_data->number_of_philo);
	while (i < philo_data->argv_data->number_of_philo)
	{
		philo_data[i].t_zero = t_zero;
		philo_data[i].last_ate = get_current_time_msec(t_zero);
		pthread_create(&thread_id_list[i], NULL, func, &philo_data[i]);
		// usleep(10000);
		i += 2;
	}	
}

int	start_philos(t_philo *philo_data)
{
	int i;
	int t_zero;
	
	i = 0;
	t_zero = get_t_zero();
	// printf("--%d--\n", philo_data[i].argv_data->number_of_philo);
	create_philo_set(0, philo_data, t_zero);
	create_philo_set(1, philo_data, t_zero);
	// i = 0;
	// while (i < philo_data->argv_data->number_of_philo)
	// {
	// 	pthread_join(thread_id_list[i], NULL);
	// 	i++;
	// }
	check_deaths(philo_data, t_zero);
	return (0);
}

int main(int argc, char **argv)
{

	t_philo *philo_data;

	if (fetch_philo_data(&philo_data, argv, argc) == 1)
		return (1);
	// printf("test : %d\n", philo_data[0].argv_data->number_of_philo);
	start_philos(philo_data);
	

	
	return (0);
}
