/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_drop_forks.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshimurahiro <yoshimurahiro@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:46:21 by yoshimurahi       #+#    #+#             */
/*   Updated: 2024/02/10 09:35:55 by yoshimurahi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


// void	take_forks(t_philo *philo)
// {
// 	pthread_mutex_lock(philo->r_fork);
// 	messages(TAKE_FORKS, philo);
// 	pthread_mutex_lock(philo->l_fork);
// 	messages(TAKE_FORKS, philo);
// }

// void	drop_forks(t_philo *philo)
// {
// 	pthread_mutex_unlock(philo->l_fork);
// 	pthread_mutex_unlock(philo->r_fork);
// }



void	take_forks(t_philo *philo)
{
    if (philo->data->num_of_philo > 1) {
        // printf("gettime: %llu\n", get_current_time() - philo->data->start_time);
        pthread_mutex_lock(philo->r_fork);
        messages(TAKE_FORKS, philo);
        pthread_mutex_lock(philo->l_fork);
        messages(TAKE_FORKS, philo);
    } else {
        pthread_mutex_lock(philo->r_fork);
        messages(TAKE_FORKS, philo);
		while(1)
			ft_usleep(0);
    }
}

void	drop_forks(t_philo *philo)
{
    if (philo->data->num_of_philo > 1) {
        pthread_mutex_unlock(philo->r_fork);
        pthread_mutex_unlock(philo->l_fork);
    } else {
        pthread_mutex_unlock(philo->r_fork);
    }
}