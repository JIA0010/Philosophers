/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjia <cjia@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 10:55:40 by yoshimurahi       #+#    #+#             */
/*   Updated: 2024/03/06 14:43:19 by cjia             ###   ########.fr       */
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
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_lock(&philo->data->lock);
	philo->eat_count++;
	philo->eating = 0;
	pthread_mutex_unlock(&philo->data->lock);
	drop_forks(philo);
}

static int	calc_meal_time(t_philo *philo)
{
	int	n;
	int	id;
	int	k;
	int	unit;

	n = philo->data->num_of_philo;
	if (n == 1)
		return (philo->data->start_time);
	id = philo->id;
	k = n / 2;
	unit = philo->data->time_to_eat / k;
	if (unit == 0)
		unit = 1;
	return (philo->data->start_time + unit * ((id * k) % n));
}

void	*routine(void *philo_p)
{
	t_philo	*philo;

	philo = (t_philo *)philo_p;
	pthread_mutex_lock(&philo->data->lock);
	philo->time_to_die = get_current_time() + philo->data->time_to_die;
	pthread_mutex_unlock(&philo->data->lock);
	while (1)
	{
		messages(THINKING, philo);
		ft_usleep(calc_meal_time(philo) - get_current_time());
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
	}
	return (NULL);
}
