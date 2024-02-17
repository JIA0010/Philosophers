/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjia <cjia@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 10:55:40 by yoshimurahi       #+#    #+#             */
/*   Updated: 2024/02/17 17:17:06 by cjia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	messages(char *str, t_philo *philo)
{
	int	time;

	pthread_mutex_lock(&philo->data->write);
	time = get_current_time() - philo->data->start_time;
	pthread_mutex_unlock(&philo->data->write);
	if (ft_strcmp(DIED, str) == 0 && philo->data->dead == 0)
	{
		printf("%d %d %s\n", time, philo->id, str);
		pthread_mutex_lock(&philo->data->dead_lock);
		philo->data->dead = 1;
		pthread_mutex_unlock(&philo->data->dead_lock);
	}
	pthread_mutex_lock(&philo->data->dead_lock);
	if (!philo->data->dead)
		printf("%d %d %s\n", time, philo->id, str);
	pthread_mutex_unlock(&philo->data->dead_lock);
}

void	eat(t_philo *philo)
{
	take_forks(philo);
	pthread_mutex_lock(&philo->lock);
	philo->eating = 1;
	philo->time_to_die = get_current_time() + philo->data->time_to_die;
	messages(EATING, philo);
	philo->eat_count++;
	ft_usleep(philo->data->time_to_eat);
	philo->eating = 0;
	pthread_mutex_unlock(&philo->lock);
	drop_forks(philo);
}
bool	test(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->dead_lock);
	if (philo->data->dead == 1)
	{
		pthread_mutex_unlock(&philo->data->dead_lock);
		return (true);
	}
	pthread_mutex_unlock(&philo->data->dead_lock);
	return (false);
}

void	*routine(void *philo_p)
{
	t_philo	*philo;

	philo = (t_philo *)philo_p;
	pthread_mutex_lock(&philo->data->lock);
	philo->time_to_die = philo->data->time_to_die + get_current_time();
	pthread_mutex_unlock(&philo->data->lock);
	if (philo->id % 2 == 0)
		ft_usleep(10);
	while (1)
	{
		if (test(philo))
			break ;
		eat(philo);
		messages(SLEEPING, philo);
		ft_usleep(philo->data->time_to_sleep);
		messages(THINKING, philo);
	}
	return (NULL);
}
