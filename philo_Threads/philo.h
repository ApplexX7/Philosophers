/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 14:03:33 by mohilali          #+#    #+#             */
/*   Updated: 2024/02/12 18:05:46 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define THINK	"is thinking"
# define DEATH	"died"
# define SLEEP	"is sleeping"
# define EATING	"is eating"
# define FORKS	"has taken a fork"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <fcntl.h>
# include <string.h>
# include <limits.h>
# include <sys/time.h>

typedef struct s_philos
{
	int				id;
	int				*died;
	pthread_t		tid;
	int				check_eat;
	int				finish_eat;
	int				number_of_eat;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	*print;
	size_t			start_time;
	size_t			last_time_eat;
	int				time_eat;
	int				time_sleep;
	int				time_death;
	int				number_eat;
	int				number_philos;

}	t_philos;

typedef struct s_thread
{
	t_philos		*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	mutex;
	size_t			start_time;
	int				died;
	int				time_eat;
	int				time_sleep;
	int				time_died;
	int				number_philos;
	int				number_eat;

}	t_threads;

size_t	get_time(void);
void	ft_print_message(int id, size_t start_time, char *message);
long	ft_atoi(const char *str);
void	ft_usleep(size_t milliseconds);
int		is_digit(char *s);
void	print_message(int id, size_t start_time, char *mssg);
void	*ft_routine(void *thread_philos);
void	*monitoring(void *data);
void	speacial_case(t_philos *philos);
int		death_loop(t_philos *philo);
void	wait_threads(t_threads *thread);
int		create_observe(pthread_t *observe, t_threads *thread);
void	create_threads(t_threads *thread);
int		create_forks(t_threads *thread);
void	ft_take_fork(t_philos *philos);

#endif