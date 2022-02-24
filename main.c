/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayafdel <ayafdel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 19:55:03 by ayafdel           #+#    #+#             */
/*   Updated: 2022/02/24 12:42:40 by ayafdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


void *func(void *vargp)
{
	t_philo *data;

	data = vargp; 

	while(1)
	{
		pthread_mutex_lock(data->left_fork);
		pthread_mutex_lock(data->right_fork);
		printf("%dms:philo %d eating\n",get_current_time_msec(data->t_zero),data->philo_id);
		sleep(1);
		pthread_mutex_unlock(data->left_fork);
		pthread_mutex_unlock(data->right_fork);
		printf("%dms:philo %d sleeping\n",get_current_time_msec(data->t_zero),data->philo_id);
		sleep(2);
	}
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
	t_argv argv_data;
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
	if (fetch_fork_data(&fork_list, argv_data.number_of_philo) == 1)
		return (1);
	*philo_data = malloc(sizeof(t_philo )  * argv_data.number_of_philo);
	while (i <  argv_data.number_of_philo)
	{

		(*philo_data)[i].left_fork = &fork_list[i];
		(*philo_data)[i].philo_id = i + 1;
		(*philo_data)[i].right_fork = &fork_list[(i + 1) % argv_data.number_of_philo];
		(*philo_data)[i].argv_data = &argv_data;
		i++;
	}
	return (0);
}

int	create_philos(t_philo *philo_data)
{
	int i;
	pthread_t *thread_id_list;
	int t_zero;
	
	thread_id_list = malloc(sizeof(pthread_t) * philo_data->argv_data->number_of_philo);

	i = 0;
	t_zero = get_t_zero();
	while (i < philo_data->argv_data->number_of_philo)
	{
		philo_data[i].t_zero = t_zero;
		pthread_create(&thread_id_list[i], NULL, func, &philo_data[i]);
		i++;	
	}
	// printf("%d\n", philo_data->argv_data->number_of_philo);
	return (0);
}

int main(int argc, char **argv)
{

	t_philo *philo_data;

	if (fetch_philo_data(&philo_data, argv, argc) == 1)
		return (1);

	create_philos(philo_data);
	while(1);
	
	return (0);
}
