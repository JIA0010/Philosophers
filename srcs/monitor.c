/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjia <cjia@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 11:29:22 by cjia              #+#    #+#             */
/*   Updated: 2024/02/21 09:31:51 by cjia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_dead(t_data *data, int i)
{
	pthread_mutex_lock(&data->lock);
	if (get_current_time() >= data->philos[i].time_to_die
		&& data->philos[i].eating == 0)
	{
		pthread_mutex_unlock(&data->lock);
		messages(DIED, &data->philos[i]);
		pthread_mutex_lock(&data->lock);
		data->dead = 1;
		pthread_mutex_unlock(&data->lock);
		return (true);
	}
	pthread_mutex_unlock(&data->lock);
	return (false);
}

bool	check_meals(t_data *data, int i)
{
	pthread_mutex_lock(&data->lock);
	if (data->philos[i].eat_count == data->num_of_times_each_philo_must_eat)
	{
		data->finished++;
		data->philos[i].eat_count++;
		pthread_mutex_unlock(&data->lock);
		return (true);
	}
	pthread_mutex_unlock(&data->lock);
	pthread_mutex_lock(&data->lock);
	if (data->finished >= data->num_of_philo)
		data->dead = 1;
	pthread_mutex_unlock(&data->lock);
	return (false);
}

void	*monitor(void *data_p)
{
	t_data	*data;
	int		i;

	data = (t_data *)data_p;
	while (1)
	{
		i = 0;
		pthread_mutex_lock(&data->lock);
		if (data->dead == 1)
		{
			pthread_mutex_unlock(&data->lock);
			return ((void *)0);
		}
		pthread_mutex_unlock(&data->lock);
		while (i < data->num_of_philo)
		{
			check_dead(data, i);
			check_meals(data, i);
			i++;
		}
	}
	return ((void *)0);
}
