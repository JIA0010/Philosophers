/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjia <cjia@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 11:38:55 by cjia              #+#    #+#             */
/*   Updated: 2024/02/16 11:38:58 by cjia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define TAKE_FORKS "has taken a fork"
# define THINKING "is thinking"
# define SLEEPING "is sleeping"
# define EATING "is eating"
# define DIED "died"

typedef struct s_philo
{
	struct s_data	*data;
	pthread_t		philo_thread;
	int				id;
	int				eat_count;
	int				eating;
	int				time_to_die;
	pthread_mutex_t	lock;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
}					t_philo;

typedef struct s_data
{
	t_philo			*philos;
	pthread_t		*tid;
	int				start_time;
	int				dead;
	int				finished;
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_times_each_philo_must_eat;
	pthread_mutex_t	lock;
	pthread_mutex_t	write;
	pthread_mutex_t	*forks;
}					t_data;

int					ft_atoi(const char *str);
bool				init_main(t_data *data, int argc, char **argv);
bool				start_philo(t_data *data);
int					get_current_time(void);
int					ft_usleep(int time);
int					one_philo(t_data *data);
void				*routine(void *philo_pointer);
void				messages(char *str, t_philo *philo);
void				eat(t_philo *philo);
int					ft_strcmp(char *s1, char *s2);
void				ft_exit(t_data *data);
void				take_forks(t_philo *philo);
void				drop_forks(t_philo *philo);
void				*monitor(void *data_p);

#endif
