/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayafdel <ayafdel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 08:57:23 by ayafdel           #+#    #+#             */
/*   Updated: 2022/03/06 10:20:50 by ayafdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	fetch_fork_data(pthread_mutex_t **forks, int n_philo)
{
	int	i;

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

int	fetch_philo_data(t_philo **philo_data, \
pthread_mutex_t **fork_list, t_argv *argv_data)
{
	int				i;
	pthread_mutex_t	*print_mutex;

	i = 0;
	print_mutex = malloc(sizeof(pthread_mutex_t));
	if (print_mutex == NULL)
		return (1);
	if (pthread_mutex_init(print_mutex, NULL) != 0)
	{
		free(print_mutex);
		return (1);
	}
	while (i < argv_data->number_of_philo)
	{
		(*philo_data)[i].print_mutex = print_mutex;
		(*philo_data)[i].philo_id = i + 1;
		(*philo_data)[i].argv_data = argv_data;
		(*philo_data)[i].left_fork = &(*fork_list)[i];
		(*philo_data)[i].right_fork = &(*fork_list)[(i + 1) \
		% argv_data->number_of_philo];
		i++;
	}
	return (0);
}

int	fetch_philos_data(t_philo **philo_data, char **argv, int argc)
{
	t_argv			*argv_data;
	pthread_mutex_t	*fork_list;
	int				i;

	i = 0;
	if (args_error(argv, argc))
	{
		ft_putstr_fd("error argument", 2);
		return (1);
	}
	if (fetch_argv_data(&argv_data, argv) == 1)
		return (1);
	if (fetch_fork_data(&fork_list, argv_data->number_of_philo) == 1)
		return (free_return(argv_data, NULL, NULL));
	*philo_data = malloc(sizeof(t_philo) * argv_data->number_of_philo);
	if (*philo_data == NULL)
		return (free_return(argv_data, fork_list, NULL));
	if (fetch_philo_data(philo_data, &fork_list, argv_data) == 1)
		return (free_return(*philo_data, argv_data, fork_list));
	return (0);
}
