/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshimurahiro <yoshimurahiro@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 10:55:40 by yoshimurahi       #+#    #+#             */
/*   Updated: 2024/02/10 09:44:32 by yoshimurahi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*supervisor(void *philo_pointer)
{
	t_philo	*philo;

	philo = (t_philo *) philo_pointer;
	while (philo->data->dead == 0)
	{
		pthread_mutex_lock(&philo->lock);
		if (get_current_time() >= philo->time_to_die && philo->eating == 0)
			messages(DIED, philo);
		if (philo->eat_count == philo->data->num_of_times_each_philo_must_eat)
		{
			pthread_mutex_lock(&philo->data->lock);
			philo->data->finished++;
			philo->eat_count++;
			pthread_mutex_unlock(&philo->data->lock);
		}
		pthread_mutex_unlock(&philo->lock);
	}
	return ((void *)0);
}


void	messages(char *str, t_philo *philo)
{
	u_int64_t	time;
	
	pthread_mutex_lock(&philo->data->write);
	time = get_current_time() - philo->data->start_time;
	if (ft_strcmp(DIED, str) == 0 && philo->data->dead == 0)
	{
		printf("%llu %d %s\n", time, philo->id, str);
		philo->data->dead = 1;
	}
	if (!philo->data->dead)
		printf("%llu %d %s\n", time, philo->id, str);
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
		ft_usleep(200);
    if (pthread_create(&philo->philo_thread, NULL, &supervisor, (void *)philo))
        return ((void *)1);
    while (philo->data->dead == 0)
    {
        eat(philo);
        messages(SLEEPING, philo);
	    ft_usleep(philo->data->time_to_sleep);
        messages(THINKING, philo);
    }
    if (pthread_join(philo->philo_thread, NULL))
        return ((void *)1);
    return ((void *)0);
}