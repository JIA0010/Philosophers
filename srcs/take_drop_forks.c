/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_drop_forks.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjia <cjia@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:46:21 by yoshimurahi       #+#    #+#             */
/*   Updated: 2024/02/21 10:11:05 by cjia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks_for_one(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->lock);
	philo->time_to_die = get_current_time() + philo->data->time_to_die;
	pthread_mutex_unlock(&philo->data->lock);
	messages(TAKE_FORKS, philo);
	while (1)
	{
		pthread_mutex_lock(&philo->data->lock);
		if (philo->data->dead == 1)
		{
			pthread_mutex_unlock(&philo->data->lock);
			return ;
		}
		if (philo->time_to_die > get_current_time() && philo->data->dead == 0)
		{
			pthread_mutex_unlock(&philo->data->lock);
			usleep(1000);
		}
	}
}

void	take_forks(t_philo *philo)
{
	if (philo->l_fork == philo->r_fork)
	{
		take_forks_for_one(philo);
		return ;
	}
	pthread_mutex_lock(philo->r_fork);
	messages(TAKE_FORKS, philo);
	pthread_mutex_lock(philo->l_fork);
	messages(TAKE_FORKS, philo);
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}
