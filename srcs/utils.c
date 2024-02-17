/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjia <cjia@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 13:00:34 by yoshimurahi       #+#    #+#             */
/*   Updated: 2024/02/17 11:51:16 by cjia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_exit(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_of_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philos[i].lock);
	}
	pthread_mutex_destroy(&data->write);
	pthread_mutex_destroy(&data->lock);
	if (data->tid)
		free(data->tid);
	if (data->forks)
		free(data->forks);
	if (data->philos)
		free(data->philos);
}

int	ft_atoi(const char *str)
{
	int	result;
	int	sign;

	result = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + *str - '0';
		str++;
	}
	return (sign * result);
}

int	get_current_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
	{
		printf("failed to gettimeofday\n");
		return (-1);
	}
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	ft_usleep(int time)
{
	int	end_time;

	// int	start;
	// start = get_current_time();
	// while ((get_current_time() - start) < time)
	// 	usleep(100);
	end_time = get_current_time() + time;
	while (end_time > get_current_time())
	{
		usleep((end_time - get_current_time()) / 4 * 1000);
	}
	return (0);
}

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 != '\0' && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*(char *)s1 - *(char *)s2);
}
