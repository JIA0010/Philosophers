/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjia <cjia@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 15:05:07 by yoshimurahi       #+#    #+#             */
/*   Updated: 2024/02/21 09:32:15 by cjia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	set_monitor(t_data *data)
{
	pthread_t	t0;

	if (pthread_create(&t0, NULL, (void *)&monitor, (void *)data))
		return (printf("error: pthread_create is failed\n"), ft_exit(data),
			false);
	pthread_detach(t0);
	return (true);
}

bool	start_routine(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philo)
	{
		if (pthread_create(&data->tid[i], NULL, &routine,
				(void *)&data->philos[i]))
			return (printf("error: pthread_create is failed\n"),
				(ft_exit(data)), false);
		i++;
	}
	return (true);
}

bool	finish_routine(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philo)
	{
		if (pthread_join(data->tid[i], NULL))
			return (printf("error: pthread_join is failed\n"), ft_exit(data),
				false);
		i++;
	}
	return (true);
}

bool	start_philo(t_data *data)
{
	if (data->num_of_philo == 1)
		return (one_philo(data));
	data->start_time = get_current_time();
	if (start_routine(data) == false)
		return (false);
	if (set_monitor(data) == false)
		return (false);
	if (finish_routine(data) == false)
		return (false);
	return (true);
}
