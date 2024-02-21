/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjia <cjia@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 10:55:40 by yoshimurahi       #+#    #+#             */
/*   Updated: 2024/02/21 09:32:03 by cjia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	messages(char *str, t_philo *philo)
{
	int	time;

	pthread_mutex_lock(&philo->data->lock);
	time = get_current_time() - philo->data->start_time;
	if (ft_strcmp(DIED, str) == 0 && philo->data->dead == 0)
	{
		printf("%d %d %s\n", time, philo->id, str);
		philo->data->dead = 1;
	}
	if (philo->data->dead == 0)
		printf("%d %d %s\n", time, philo->id, str);
	pthread_mutex_unlock(&philo->data->lock);
}

void	eat(t_philo *philo)
{
	take_forks(philo);
	pthread_mutex_lock(&philo->data->lock);
	philo->eating = 1;
	philo->time_to_die = get_current_time() + philo->data->time_to_die;
	pthread_mutex_unlock(&philo->data->lock);
	messages(EATING, philo);
	pthread_mutex_lock(&philo->data->lock);
	philo->eat_count++;
	philo->eating = 0;
	pthread_mutex_unlock(&philo->data->lock);
	ft_usleep(philo->data->time_to_eat);
	drop_forks(philo);
}

void	*routine(void *philo_p)
{
	t_philo	*philo;

	philo = (t_philo *)philo_p;
	if (philo->id % 2 == 0)
		ft_usleep(10);
	while (1)
	{
		pthread_mutex_lock(&philo->data->lock);
		if (philo->data->dead)
		{
			pthread_mutex_unlock(&philo->data->lock);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->data->lock);
		eat(philo);
		messages(SLEEPING, philo);
		ft_usleep(philo->data->time_to_sleep);
		messages(THINKING, philo);
	}
	return (NULL);
}
