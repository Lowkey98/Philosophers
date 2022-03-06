/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayafdel <ayafdel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 10:15:26 by ayafdel           #+#    #+#             */
/*   Updated: 2022/03/06 10:15:54 by ayafdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef struct s_argv {
	int	number_of_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_eats;
}				t_argv;
typedef struct s_philo {
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*print_mutex;
	t_argv			*argv_data;
	int				philo_id;
	long			t_zero;
	int				last_ate;
	int				times_ate;
}				t_philo;

void	ft_putstr_fd(char *s, int fd);
int		ft_atoi(const char *str);
int		get_current_time_msec(int t_zero);
int		get_t_zero(void);
int		fetch_argv_data(t_argv **argv_data, char **argv);
int		arg_error(char *str);
int		args_error(char **argv, int argc);
int		ft_strlen(char *str);
int		fetch_philos_data(t_philo **philo_data, char **argv, int argc);
void	ft_usleep(int period);
void	destroy_free(t_philo *philo_data);
int		free_return(void *arg1, void *arg2, void *arg3);
void	*philo_routine(void *vargp);

#endif