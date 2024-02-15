/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjia <cjia@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 10:55:40 by yoshimurahi       #+#    #+#             */
/*   Updated: 2024/02/15 14:14:40 by cjia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int 	supervisor(void *philo_pointer)
{
	t_philo	*philo;

	philo = (t_philo *) philo_pointer;
	pthread_mutex_lock(&philo->lock);
	if (get_current_time() >= philo->time_to_die && philo->eating == 0)
	{
		messages(DIED, philo);
		pthread_mutex_unlock(&philo->lock);
		return (2);
	}
	if (philo->eat_count == philo->data->num_of_times_each_philo_must_eat)
	{
		pthread_mutex_lock(&philo->data->lock);
		philo->data->finished++;
		philo->eat_count++;
		pthread_mutex_unlock(&philo->data->lock);
		pthread_mutex_unlock(&philo->lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->lock);
	return (0);
}


void	messages(char *str, t_philo *philo)
{
	int	time;

	pthread_mutex_lock(&philo->data->write);
	time = get_current_time() - philo->data->start_time;
	if (ft_strcmp(DIED, str) == 0 && philo->data->dead == 0)
	{
		printf("%d %d %s\n", time, philo->id, str);
		philo->data->dead = 1;
	}
	if (!philo->data->dead)
		printf("%d %d %s\n", time, philo->id, str);
	pthread_mutex_unlock(&philo->data->write);
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

void *routine(void *philo_pointer)
{
    t_philo	*philo;

    philo = (t_philo *) philo_pointer;
    philo->time_to_die = philo->data->time_to_die + get_current_time();
	if(philo->id % 2 == 0)
		ft_usleep(10);
    while (philo->data->dead == 0)
    {
		if(supervisor(philo) == 2 || supervisor(philo) == 1)
			break;
        eat(philo);
        messages(SLEEPING, philo);
	    ft_usleep(philo->data->time_to_sleep);
        messages(THINKING, philo);
    }
    return ((void *)0);
}
