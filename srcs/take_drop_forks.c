/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_drop_forks.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjia <cjia@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:46:21 by yoshimurahi       #+#    #+#             */
/*   Updated: 2024/02/17 11:57:07 by cjia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	if (philo->l_fork == philo->r_fork)
	{
		pthread_mutex_lock(philo->l_fork);
		messages(TAKE_FORKS, philo);
		while (philo->time_to_die > get_current_time())
		{
			pthread_mutex_lock(&philo->data->write);
			if (philo->data->dead == 1)
			{
				pthread_mutex_unlock(&philo->data->write);
				break ;
			}
			pthread_mutex_unlock(&philo->data->write);
			ft_usleep(1000);
		}
		pthread_mutex_unlock(philo->l_fork);
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
