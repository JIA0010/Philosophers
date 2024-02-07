/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_drop_forks.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshimurahiro <yoshimurahiro@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:46:21 by yoshimurahi       #+#    #+#             */
/*   Updated: 2024/02/07 12:48:06 by yoshimurahi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	messages(TAKE_FORKS, philo);
	pthread_mutex_lock(philo->l_fork);
	messages(TAKE_FORKS, philo);
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	messages(SLEEPING, philo);
	ft_usleep(philo->data->time_to_sleep);
}