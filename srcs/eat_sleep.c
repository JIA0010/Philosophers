/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshimurahiro <yoshimurahiro@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 10:55:40 by yoshimurahi       #+#    #+#             */
/*   Updated: 2024/02/06 17:01:10 by yoshimurahi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	messages(char *str, t_philo *philo)
{
	u_int64_t	time;

	// printf("get_current_time() = %d\n", get_current_time());
	// printf("philo->data->start_time = %llu\n", philo->data->start_time);
	pthread_mutex_lock(&philo->data->write);
	time = get_current_time() - philo->data->start_time;
	if (ft_strcmp("DIED", str) == 0 && philo->data->dead == 0)
	{
		printf("%llu %d %s\n", time, philo->id, str);
		philo->data->dead = 1;
	}
	if (!philo->data->dead)
		printf("%llu %d %s\n", time, philo->id, str);
	pthread_mutex_unlock(&philo->data->write);
}

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	messages("TAKE_FORKS", philo);
	pthread_mutex_lock(philo->l_fork);
	messages("TAKE_FORKS", philo);
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	messages("SLEEPING", philo);
	ft_usleep(philo->data->time_to_sleep);
}

void	eat(t_philo *philo)
{
	take_forks(philo);
	pthread_mutex_lock(&philo->lock);
	philo->eating = 1;
	philo->time_to_die = get_current_time() + philo->data->time_to_die;
	messages("EATING", philo);
	philo->eat_count++;
	ft_usleep(philo->data->time_to_eat);
	philo->eating = 0;
	pthread_mutex_unlock(&philo->lock);
	drop_forks(philo);
}
