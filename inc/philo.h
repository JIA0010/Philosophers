#ifndef PHILO_H
# define PHILO_H

# include <stdbool.h>
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
    struct s_data	*data;
	pthread_t		philo_thread;
	int				id;
	int				eat_count;
	int				eating;
	uint64_t		time_to_die;
	pthread_mutex_t	lock;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
}               t_philo;


typedef struct s_data
{
    t_philo *philos;
    pthread_t		*tid;
    uint64_t	start_time;
    int				dead;
    int				finished;
    int     num_of_philo;
    int     time_to_die;
    int     time_to_eat;
    int     time_to_sleep;
    int     num_of_times_each_philo_must_eat;
    pthread_mutex_t   lock;
    pthread_mutex_t write;
    pthread_mutex_t *forks;
}               t_data;

int 	ft_atoi(const char *str);
bool    init_main(t_data *data, int argc, char **argv);
bool    start_philo(t_data  *data);
int	get_current_time(void);
int	ft_usleep(useconds_t time);
int	one_philo(t_data *data);
void *routine(void *philo_pointer);
void	messages(char *str, t_philo *philo);
void	eat(t_philo *philo);
int	ft_strcmp(char *s1, char *s2);
void	ft_exit(t_data *data);

#endif