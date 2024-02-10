/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 14:03:33 by mohilali          #+#    #+#             */
/*   Updated: 2024/02/10 15:02:46 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <fcntl.h>
# include <string.h>
# include <limits.h>
# include <sys/time.h>

typedef struct s_philo
{
	pthread_t		tid;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*print;
	pthread_mutex_t	*deadlock;
	pthread_mutex_t	*protect;
	pthread_mutex_t	*mutex;
	int				number_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eating;
	int				*exit;
	int				id;
	int				number_of_eat;
	int				not_died;
	int				*died;
	size_t			start_time;
	size_t			last_eat;
}	t_philo;

typedef struct s_threads
{
	int				died;
	t_philo			*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	lock_time;
	pthread_mutex_t	mutex;
	pthread_mutex_t	deadlock;
	pthread_mutex_t	protect;
	int				number_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_eats;
	int				exit;
	int				not_died;
}	t_threads;

/*helper function*/
void	*monitoring(void *thread);
int		number_of_eat(t_philo *philo);
int		dead_loop(t_philo *philo);
size_t	get_time(void);
void	ft_print_message(int id, size_t start_time, char *message, int died);
long	ft_atoi(const char *str);
void	ft_usleep(size_t milliseconds);
void	*routine(void *philo);
void	ft_thinking(t_philo	philo);
void	ft_sleeping(t_philo	philo);
void	ft_eating(t_philo	*philo);
void	ft_usleep(size_t milliseconds);
void	ft_take_fork(t_philo philo);
int		is_digit(char *s);
void	create_philos(t_threads *threads);

#endif