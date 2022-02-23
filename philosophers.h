#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct s_argv {
    int number_of_philosophers;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int number_of_eats;
} t_argv;
typedef struct s_philo {
    int philo_n;
    pthread_mutex_t *right_fork;
    pthread_mutex_t *left_fork;
    t_argv argv_data;
} t_philo;

void	ft_putstr_fd(char *s, int fd);
int     ft_atoi(const char *str);