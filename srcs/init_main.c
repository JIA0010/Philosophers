/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshimurahiro <yoshimurahiro@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 12:36:33 by yoshimurahi       #+#    #+#             */
/*   Updated: 2024/02/08 15:30:57 by yoshimurahi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	give_philos_the_forks(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_of_philo);
	if (data->forks == NULL)
		return (false);
	i = 0;
	data->philos[0].l_fork = &data->forks[0];
	data->philos[0].r_fork = &data->forks[data->num_of_philo - 1];
	i = 1;
	while (i < data->num_of_philo)
	{
		data->philos[i].l_fork = &data->forks[i];
		data->philos[i].r_fork = &data->forks[i - 1];
		i++;
	}
	return (0);
}

static bool init_philo(t_data *data)
{
    int i;

    i = 0;
    data->philos = malloc(sizeof(t_philo) * data->num_of_philo);
    if(data->philos == NULL)
        return (false);
    while(i < data->num_of_philo)
    {
        data->philos[i].id = i + 1;
        data->philos[i].eat_count = 0;
        data->philos[i].eating = 0;
        data->philos[i].time_to_die = 0;
        data->philos[i].data = data;
        data->philos[i].philo_thread = NULL;
        pthread_mutex_init(&data->philos[i].lock, NULL);
        i++;
    }
    give_philos_the_forks(data);
	return (true);
}

static bool init_data(t_data *data, int argc, char **argv)
{
    int i;

    i = -1;
    data->start_time = 0;
    data->dead = 0;
	data->finished = 0;
    data->num_of_philo = ft_atoi(argv[1]);
    data->time_to_die = ft_atoi(argv[2]);
    data->time_to_eat = ft_atoi(argv[3]);
    data->time_to_sleep = ft_atoi(argv[4]);
    pthread_mutex_init(&data->lock, NULL);
    pthread_mutex_init(&data->write, NULL);
    while (++i < data->num_of_philo)
		pthread_mutex_init(&data->forks[i], NULL);
    data->tid = malloc(sizeof(pthread_t) * data->num_of_philo);
	if (!data->tid)
		return (printf("error"), false);
    return (true);
}

bool   init_main(t_data *data, int argc, char **argv)
{
    if(init_data(data, argc, argv) == false)
        return (printf("error: init_data failed"), ft_exit(data), false);
    if(init_philo(data) == false)
        return (printf("error: init_philo failed"), ft_exit(data), false);
    if(argc == 6)
        data->num_of_times_each_philo_must_eat = ft_atoi(argv[5]);
    if (data->num_of_philo <= 0 || data->num_of_philo > 200 || data->time_to_die < 0
		|| data->time_to_eat < 0 || data->time_to_sleep < 0 || (argc == 6 && data->num_of_times_each_philo_must_eat < 0))
		return (printf("error: invalid args\n"), ft_exit(data), false);
    return (true);
}