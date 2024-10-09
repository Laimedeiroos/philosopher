#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_philosopher
{
    int             id;
    long            last_meal;
    int             meals_eaten;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    struct s_data   *data;
}   t_philosopher;

typedef struct s_data
{
    int             num_philos;
    long            time_to_die;
    long            time_to_eat;
    long            time_to_sleep;
    int             must_eat_count;
    int             simulation_ended;
    pthread_mutex_t *forks;
    pthread_mutex_t print_mutex;
    t_philosopher   *philosophers;
    long            start_time;
}   t_data;

void *philosopher_life(void *arg);

void print_status(t_philosopher *philo, const char *status);
long current_time(void);

#endif
