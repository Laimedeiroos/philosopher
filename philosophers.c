#include "philo.h"

static void pick_up_forks(t_philosopher *philo)
{
    pthread_mutex_lock(philo->left_fork);
    print_status(philo, "has taken a fork");

    pthread_mutex_lock(philo->right_fork);
    print_status(philo, "has taken a fork");
}

static void release_forks(t_philosopher *philo)
{
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
}

static void dine(t_philosopher *philo)
{
    print_status(philo, "is eating");
    philo->last_meal = current_time();
    usleep(philo->data->time_to_eat * 1000);
    philo->meals_eaten++;
}

static void rest_and_think(t_philosopher *philo)
{
    print_status(philo, "is sleeping");
    usleep(philo->data->time_to_sleep * 1000);

    print_status(philo, "is thinking");
}

void *philosopher_life(void *arg)
{
    t_philosopher *philo = (t_philosopher *)arg;

    while (!philo->data->simulation_ended)
    {
        pick_up_forks(philo);
        dine(philo);
        release_forks(philo);
        rest_and_think(philo);
    }
    
    return (NULL);
}
