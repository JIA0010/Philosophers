/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjia <cjia@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 11:28:23 by cjia              #+#    #+#             */
/*   Updated: 2024/03/06 14:36:18 by cjia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor_for_one(void *data_p)
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
			if (check_dead(data, i) == true)
				return ((void *)0);
			i++;
		}
	}
	return ((void *)0);
}

int	one_philo(t_data *data)
{
	pthread_t	t0;

	data->philos[0].time_to_die = get_current_time() + data->time_to_die;
	if (pthread_create(&t0, NULL, (void *)&monitor_for_one, (void *)data))
		return (printf("error: pthread_create is failed\n"), ft_exit(data),
			false);
	pthread_detach(t0);
	data->start_time = get_current_time();
	if (pthread_create(&t0, NULL, &routine, &data->philos[0]))
		return (printf("error: pthread_create is failed\n"), ft_exit(data),
			false);
	if (pthread_join(t0, NULL))
		return (printf("error: pthread_join is failed\n"), ft_exit(data),
			false);
	ft_exit(data);
	return (0);
}
