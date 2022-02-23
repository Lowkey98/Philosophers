/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayafdel <ayafdel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 19:55:03 by ayafdel           #+#    #+#             */
/*   Updated: 2022/02/23 18:22:36 by ayafdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


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

void *func(void *vargp)
{
    t_philo *data;

    data = vargp; 
    // printf("Printing from the thread\n");
    while(1)
    {
        pthread_mutex_lock(data->left_fork);
        pthread_mutex_lock(data->right_fork);
        printf("philo %d eating\n",data->philo_n);
        sleep(1);
        pthread_mutex_unlock(data->left_fork);
        pthread_mutex_unlock(data->right_fork);
        printf("philo %d sleeping\n",data->philo_n);
        sleep(2);
    }
    // printf("value =%d\n", a);
    return NULL;
}


int fetch_argv_data(t_argv *argv_data, char **argv)
{
    argv_data->number_of_philosophers = ft_atoi(argv[1]);
    argv_data->time_to_die = ft_atoi(argv[2]);
    argv_data->time_to_eat = ft_atoi(argv[3]);
    argv_data->time_to_sleep = ft_atoi(argv[4]);
    argv_data->number_of_eats = -1;
    if (argv[5])
        argv_data->number_of_eats = ft_atoi(argv[5]);
    return (0);
}
int		arg_error(char *str)
{
	int i;

	i = 0;
	if (str[0] == '0' || str[0] == '\0')
		return (1);

	while (str[i] >= '0' && str[i] <= '9')
	{
		if (str[i + 1] == '\0')
			return (0);
		i++;
	}
    // printf("%s\n", str);
	return (1);
}

int     args_error(char **argv, int argc)
{
    int i;
    int j;

    j = 0;
    i = 1;
    
    if (argc != 5 && argc != 6)
        return (1);
    while (argv[i])
    {
        if (arg_error(argv[i]))
            return (1);
        i++;
    }
    return (0);
}

int     fetch_philo_data(t_philo *philo_data, char **argv, int argc)
{
    t_argv argv_data;

    if (args_error(argv, argc))
    {
        ft_putstr_fd("error argument", 2);
        return (1);
    }
    if (fetch_argv_data(&argv_data, argv) == 1)
        return (1);
    printf("%d\n", argv_data.number_of_philosophers);
    printf("%d\n", argv_data.time_to_die);
    printf("%d\n", argv_data.time_to_eat);
    printf("%d\n", argv_data.time_to_sleep);
    printf("%d\n", argv_data.number_of_eats);
    philo_data->argv_data = argv_data;
    return (0);
}


int main(int argc, char **argv)
{
    //int t_zero = get_t_zero();
    
    // printf("%ld\n",);
    // printf("%d\n",tv.tv_usec);
    //printf("%d\n", get_current_time_msec(t_zero));
    t_philo philo_data;

    if (fetch_philo_data(&philo_data, argv, argc) == 1)
        return (1);
    // pthread_t *thread_list;
    
    // thread_list = malloc(sizeof(pthread_t) * atoi(argv[1]));
    // philo_t data = get_data();
    // pthread_t thread_id1;
    // pthread_t thread_id2;
    // pthread_mutex_t mutex1;
    // pthread_mutex_t mutex2;
    // pthread_mutex_init(&mutex1, NULL);
    // pthread_mutex_init(&mutex2, NULL);
    // philo_t data[2];
    // data[0].left_fork = &mutex1;
    // data[0].right_fork = &mutex2;
    // data[1].left_fork = &mutex2;
    // data[1].right_fork = &mutex1;
    // data[0].philo_n = 1;
    // data[1].philo_n = 2;
    // pthread_create(&thread_id1, NULL, func, &data[0]);
    // sleep(1);
    // pthread_create(&thread_id2, NULL, func, &data[1]);
    // //sleep(1);
    // // print_time_now();
    // // pthread_t thread_id2;
    // // int a = 1;
    // // int b = 2;
    // // printf("Before Thread\n");
    // // pthread_create(&thread_id2, NULL, func, &b);
    // pthread_join(thread_id1, NULL);
    // pthread_join(thread_id2, NULL);
    // // printf("After Thread\n");
    
    return (0);
}
