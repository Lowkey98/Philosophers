/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayafdel <ayafdel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 12:38:56 by ayafdel           #+#    #+#             */
/*   Updated: 2022/02/24 12:39:19 by ayafdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philosophers.h"

int     get_current_time_msec(int t_zero)
{
	struct timeval  tv;
	
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + (tv.tv_usec / 1000) - t_zero);
}

int get_t_zero()
{
	struct timeval  tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + (tv.tv_usec / 1000));
}
