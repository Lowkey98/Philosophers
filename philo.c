/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayafdel <ayafdel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 09:10:19 by ayafdel           #+#    #+#             */
/*   Updated: 2022/03/06 09:27:11 by ayafdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	lock_and_print(pthread_mutex_t *mutex, char *str, int arg_one, int arg_two)
{
	if (pthread_mutex_lock(mutex) != 0)
		return (1);
	printf(str, get_current_time_msec(arg_one), arg_two);
	if (pthread_mutex_unlock(mutex) != 0)
		return (1);
	return (0);
}

int	pick_up_forks(t_philo *data)
{
	pthread_mutex_lock(data->left_fork);
	lock_and_print(data->print_mutex, "%d philo %d has taking left fork\n"\
	, data->t_zero, data->philo_id);
	pthread_mutex_lock(data->right_fork);
	lock_and_print(data->print_mutex, "%d philo %d has taking right fork\n"\
	, data->t_zero, data->philo_id);
	return (0);
}

int	put_down_forks(t_philo *data)
{
	pthread_mutex_unlock(data->left_fork);
	pthread_mutex_unlock(data->right_fork);
	return (0);
}

int	sleep_think(t_philo *data)
{
	lock_and_print(data->print_mutex, "%d philo %d sleeping\n"\
	, data->t_zero, data->philo_id);
	ft_usleep(data->argv_data->time_to_sleep * 1000);
	lock_and_print(data->print_mutex, "%d philo %d thinking\n"\
	, data->t_zero, data->philo_id);
	return (0);
}

void	*philo_routine(void *vargp)
{
	t_philo	*data;

	data = vargp;
	while (1)
	{
		pick_up_forks(data);
		data->last_ate = get_current_time_msec(data->t_zero);
		lock_and_print(data->print_mutex, "%d philo %d eating\n"\
		, data->t_zero, data->philo_id);
		ft_usleep(data->argv_data->time_to_eat * 1000);
		data->times_ate++;
		put_down_forks(data);
		sleep_think(data);
	}
	return (NULL);
}
