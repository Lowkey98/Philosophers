/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayafdel <ayafdel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 12:38:56 by ayafdel           #+#    #+#             */
/*   Updated: 2022/03/06 09:30:05 by ayafdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	get_current_time_usec(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000000 + tv.tv_usec);
}

void	ft_usleep(int period)
{
	int	end_time;

	end_time = get_current_time_usec() + period;
	usleep(period - 1000);
	while (get_current_time_usec() < end_time)
		usleep(100);
}

int	get_current_time_msec(int t_zero)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + (tv.tv_usec / 1000) - t_zero);
}

int	get_t_zero(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + (tv.tv_usec / 1000));
}
