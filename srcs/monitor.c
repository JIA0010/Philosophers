/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjia <cjia@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 11:29:22 by cjia              #+#    #+#             */
/*   Updated: 2024/02/16 11:29:55 by cjia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool    check_dead(t_data *data, int i)
{
        if (get_current_time() >= data->philos[i].time_to_die && data->philos[i].eating == 0)
        {
            pthread_mutex_lock(&data->philos[i].lock);
            messages(DIED, &data->philos[i]);
            pthread_mutex_unlock(&data->philos[i].lock);
            data->dead = 1;
            return (true);
        }
    return (false);
}

bool    check_meals(t_data *data, int i)
{
    if (data->philos[i].eat_count == data->num_of_times_each_philo_must_eat)
    {
        pthread_mutex_lock(&data->lock);
        data->finished++;
        data->philos[i].eat_count++;
        pthread_mutex_unlock(&data->lock);
        return (true);
    }
    pthread_mutex_lock(&data->lock);
    if (data->finished >= data->num_of_philo)
        data->dead = 1;
    pthread_mutex_unlock(&data->lock);
    return (false);
}

void	*monitor(void *data_p)
{
    t_data *data = (t_data *)data_p;

    int	i;
	while (data->dead == 0)
	{
        i = 0;
        while (i < data->num_of_philo)
        {
            check_dead(data, i);
            check_meals(data, i);
            i++;
        }
	}
	return ((void *)0);
}
