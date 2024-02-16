/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjia <cjia@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 11:28:23 by cjia              #+#    #+#             */
/*   Updated: 2024/02/16 12:53:36 by cjia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor_for_one(void *data_p)
{
	int		i;
	t_data	*data;

	data = (t_data *)data_p;
	i = 0;
	while (data->dead == 0)
	{
		if (get_current_time() >= data->philos[i].time_to_die
			&& data->philos[i].eating == 0)
		{
			pthread_mutex_lock(&data->philos[i].lock);
			messages(DIED, &data->philos[i]);
			pthread_mutex_unlock(&data->philos[i].lock);
		}
	}
	return ((void *)0);
}

int	one_philo(t_data *data)
{
	pthread_t	t0;

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
