/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshimurahiro <yoshimurahiro@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 15:05:07 by yoshimurahi       #+#    #+#             */
/*   Updated: 2024/02/10 10:16:33 by yoshimurahi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor(void *data_pointer)
{
	t_philo	*philo;

	philo = (t_philo *) data_pointer;
	pthread_mutex_lock(&philo->data->write);
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
    // pthread_t    t0;
	// data->start_time = get_current_time();
	// if (pthread_create(&t0, NULL, &routine, &data->philos[0]))
	// 	return (printf("error\n"), ft_exit(data), false);
    // if (pthread_join(t0, NULL)) 
    //     return (printf("error\n"),ft_exit(data), false);
	// // ft_exit(data);
	// return (0);
    data->start_time = get_current_time();
	if (pthread_create(&data->tid[0], NULL, &routine, &data->philos[0]))
		return (printf("error"), ft_exit(data), false);
	pthread_detach(data->tid[0]);
	while (data->dead == 0)
		ft_usleep(0);
	ft_exit(data);
	return (0);
}

bool	set_monitor(t_data *data)
{
    pthread_t	t0;

    if (data-> num_of_times_each_philo_must_eat > 0)
	{
		if (pthread_create(&t0, NULL, &monitor, &data->philos[0]))
            return (printf("error"), ft_exit(data), false);
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
        // ft_usleep(1);
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
    if(data->num_of_philo == 1)
       return(one_philo(data));
    data->start_time = get_current_time();
    if(set_monitor(data) == false)
        return (false);
    if(start_routine(data) == false)
        return false;
    if(finish_routine(data) == false)
        return (false);
    return (true);
}