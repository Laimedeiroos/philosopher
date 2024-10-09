#include "philo.h"

void print_status(t_philosopher *philo, const char *status)
{
    long timestamp = current_time() - philo->data->start_time;

    pthread_mutex_lock(&philo->data->print_mutex);
    if (!philo->data->simulation_ended)
        printf("%ld %d %s\n", timestamp, philo->id, status);
    pthread_mutex_unlock(&philo->data->print_mutex);
}

long current_time(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
