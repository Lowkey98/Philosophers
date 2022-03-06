/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayafdel <ayafdel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 09:00:10 by ayafdel           #+#    #+#             */
/*   Updated: 2022/03/06 09:21:02 by ayafdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	destroy_free(t_philo *philo_data)
{
	int	i;
	int	n;

	i = 0;
	n = philo_data->argv_data->number_of_philo;
	while (i < n)
	{
		pthread_mutex_destroy(philo_data[i].left_fork);
		break ;
		i++;
	}
	free(philo_data[0].left_fork);
	pthread_mutex_destroy(philo_data->print_mutex);
	free(philo_data->print_mutex);
	free(philo_data->argv_data);
	free(philo_data);
}

int	free_return(void *arg1, void *arg2, void *arg3)
{
	free(arg1);
	free(arg2);
	free(arg3);
	return (1);
}
