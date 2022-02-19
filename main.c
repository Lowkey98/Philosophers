/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayafdel <ayafdel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 19:55:03 by ayafdel           #+#    #+#             */
/*   Updated: 2022/02/19 10:57:30 by ayafdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void *func(void *vargp)
{
    int a;

    a = *(int*)(vargp); 
    // printf("Printing from the thread\n");
    printf("value = %d\n", a);
    return NULL;
}

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

int main()
{

    int t_zero = get_t_zero();
    
    // printf("%ld\n",);
    // printf("%d\n",tv.tv_usec);
    printf("%d\n", get_current_time_msec(t_zero));
 
    //sleep(1);
    // print_time_now();
    // pthread_t thread_id1;
    // pthread_t thread_id2;
    // int a = 1;
    // int b = 2;
    // printf("Before Thread\n");
    // pthread_create(&thread_id1, NULL, func, &a);
    // pthread_create(&thread_id2, NULL, func, &b);
    // pthread_join(thread_id1, NULL);
    // pthread_join(thread_id2, NULL);
    // printf("After Thread\n");
    
    return (0);
}

void    print()
{
    printf("hello");
}