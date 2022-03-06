/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayafdel <ayafdel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 19:55:03 by ayafdel           #+#    #+#             */
/*   Updated: 2022/03/06 10:00:59 by ayafdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	stop_simulation(t_philo	*philo_data, int reason, int t_zero, int i)
{
	pthread_mutex_lock(philo_data->print_mutex);
	if (reason == 1)
		printf("%d ms: philo %d DIED\n"\
		, get_current_time_msec(t_zero), philo_data[i].philo_id);
	if (reason == 2)
		printf("%dms :EVERYONE ATE atleast %d times\n"\
		, get_current_time_msec(philo_data->t_zero) \
		, philo_data->argv_data->number_of_eats);
	return (0);
}

int	check_deaths(t_philo *philo_data, int t_zero)
{
	int	i;
	int	ate_flag;

	ate_flag = 1;
	i = 0;
	while (1)
	{
		while (i < philo_data->argv_data->number_of_philo)
		{
			if (get_current_time_msec(t_zero) - \
			philo_data[i].last_ate > philo_data[i].argv_data->time_to_die)
				return (stop_simulation(philo_data, 1, t_zero, i));
			if (philo_data->argv_data->number_of_eats != -1)
				if (philo_data[i].times_ate \
				< philo_data->argv_data->number_of_eats)
					ate_flag = 0;
			i++;
		}
		if (ate_flag && philo_data->argv_data->number_of_eats != -1)
			return (stop_simulation(philo_data, 2, t_zero, i));
		i = 0;
		ate_flag = 1;
	}
}

int	create_philo_set(pthread_t *thread_id_list, \
int i, t_philo *philo_data, int t_zero)
{
	while (i < philo_data->argv_data->number_of_philo)
	{
		philo_data[i].t_zero = t_zero;
		philo_data[i].times_ate = 0;
		philo_data[i].last_ate = get_current_time_msec(t_zero);
		pthread_create(&thread_id_list[i], NULL, philo_routine, &philo_data[i]);
		usleep(100);
		i += 2;
	}
	return (0);
}

int	start_philos(t_philo *philo_data, int t_zero)
{
	int			i;
	pthread_t	*thread_id_list;

	i = 0;
	thread_id_list = malloc(sizeof(pthread_t) \
	* philo_data->argv_data->number_of_philo);
	if (thread_id_list == NULL)
		return (1);
	if (create_philo_set(thread_id_list, 0, philo_data, t_zero) == 1)
		return (1);
	usleep(100);
	if (create_philo_set(thread_id_list, 1, philo_data, t_zero) == 1)
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo	*philo_data;
	int		t_zero;

	t_zero = get_t_zero();
	if (fetch_philos_data(&philo_data, argv, argc) == 1)
		return (1);
	if (start_philos(philo_data, t_zero) == 1)
	{
		destroy_free(philo_data);
		return (1);
	}
	check_deaths(philo_data, t_zero);
	destroy_free(philo_data);
	return (0);
}
