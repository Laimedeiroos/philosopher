#include "philo.h"

static void initialize_data(t_data *data, int argc, char **argv)
{
    data->num_philos = atoi(argv[1]);
    data->time_to_die = atol(argv[2]);
    data->time_to_eat = atol(argv[3]);
    data->time_to_sleep = atol(argv[4]);
    data->must_eat_count = (argc == 6) ? atoi(argv[5]) : -1;
    data->simulation_ended = 0;

    data->philosophers = malloc(sizeof(t_philosopher) * data->num_philos);
    data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
    data->start_time = current_time();
}

int main(int argc, char **argv)
{
    if (argc < 5 || argc > 6)
    {
        printf("Usage: %s num_philos time_to_die time_to_eat time_to_sleep [must_eat_count]\n", argv[0]);
        return (1);
    }

    t_data data;

    initialize_data(&data, argc, argv);
    
    pthread_mutex_init(&data.print_mutex, NULL);
    for (int i = 0; i < data.num_philos; i++)
        pthread_mutex_init(&data.forks[i], NULL);

    pthread_t threads[data.num_philos];

    for (int i = 0; i < data.num_philos; i++)
    {
        data.philosophers[i].id = i + 1;
        data.philosophers[i].last_meal = current_time();
        data.philosophers[i].meals_eaten = 0;
        data.philosophers[i].left_fork = &data.forks[i];
        data.philosophers[i].right_fork = &data.forks[(i + 1) % data.num_philos];
        data.philosophers[i].data = &data;

        pthread_create(&threads[i], NULL, philosopher_life, &data.philosophers[i]);
    }

    for (int i = 0; i < data.num_philos; i++)
        pthread_join(threads[i], NULL);

    for (int i = 0; i < data.num_philos; i++)
        pthread_mutex_destroy(&data.forks[i]);
    pthread_mutex_destroy(&data.print_mutex);

    free(data.philosophers);
    free(data.forks);

    return (0);
}
