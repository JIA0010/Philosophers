/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshimurahiro <yoshimurahiro@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 15:05:07 by yoshimurahi       #+#    #+#             */
/*   Updated: 2024/02/07 12:35:39 by yoshimurahi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor(void *data_pointer)
{
	t_philo	*philo;

	philo = (t_philo *) data_pointer;
	pthread_mutex_lock(&philo->data->write);
	printf("data val: %d\n", philo->data->dead);
	pthread_mutex_unlock(&philo->data->write);
	while (philo->data->dead == 0)
	{
		pthread_mutex_lock(&philo->lock);
		if (philo->data->finished >= philo->data->num_of_philo)
			philo->data->dead = 1;
		pthread_mutex_unlock(&philo->lock);
	}
	return ((void *)0);
}

int	one_philo(t_data *data)
{
	data->start_time = get_current_time();
	if (pthread_create(&data->tid[0], NULL, &routine, &data->philos[0]))
		return (printf("TH_ERR"), ft_exit(data), false);
	pthread_detach(data->tid[0]);
	while (data->dead == 0)
		ft_usleep(0);
	ft_exit(data);
	return (0);
}

void	*supervisor(void *philo_pointer)
{
	t_philo	*philo;

	philo = (t_philo *) philo_pointer;
	while (philo->data->dead == 0)
	{
		pthread_mutex_lock(&philo->lock);
		if (get_current_time() >= philo->time_to_die && philo->eating == 0)
			messages("DIED", philo);
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

void *routine(void *philo_pointer)
{
    t_philo	*philo;

    philo = (t_philo *) philo_pointer;
    philo->time_to_die = philo->data->time_to_die + get_current_time();
    if (pthread_create(&philo->philo_thread, NULL, &supervisor, (void *)philo))
        return ((void *)1);
    while (philo->data->dead == 0)
    {
        eat(philo);
        messages("SLEEPING", philo);
	    ft_usleep(philo->data->time_to_sleep);
        messages("THINKING", philo);
    }
    if (pthread_join(philo->philo_thread, NULL))
        return ((void *)1);
    return ((void *)0);
}

bool	set_monitor(t_data *data)
{
    pthread_t	t0;

    if (data-> num_of_times_each_philo_must_eat > 0)
	{
		if (pthread_create(&t0, NULL, &monitor, &data->philos[0]))
            return (printf("TH_ERR"), ft_exit(data), false);
	}
    return (true);
}

bool start_routine(t_data *data)
{
    int i;

    i = 0;
    while(i < data->num_of_philo)
    {
        if(pthread_create(&data->tid[i], NULL, &routine, (void *)&data->philos[i]))
            return (printf("error\n"), (ft_exit(data)), false);
        ft_usleep(1);
        i++;
    }
    return (true);
}

bool finish_routine(t_data *data)
{
    int i;

    i = 0;
    while(i < data->num_of_philo)
    {
        if(pthread_join(data->tid[i], NULL))
            return(printf("error\n"), ft_exit(data), false);
        i++;
    }
    return (true);
}

bool    start_philo(t_data  *data)
{
    int i;
        
    i = -1;
    if(data->num_of_philo == 1)
       return(one_philo(data));
    data->start_time = get_current_time();
    if(set_monitor(data) == false)
        return (false);
    if(start_routine(data) == false)
        return false;
    i = -1;
    if(finish_routine(data) == false)
        return (false);
    return (true);
}