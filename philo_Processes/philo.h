/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 19:01:32 by mohilali          #+#    #+#             */
/*   Updated: 2025/02/28 15:26:17 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define THINK	"is thinking"
# define DEATH	"died"
# define SLEEP	"is sleeping"
# define EATING	"is eating"
# define FORKS	"has taken a fork"
# define SEM_AMPHORE "/sem_process"
# define SEM_FORKS "/sem_forks"
# define SEM_DEATH "/sem_death"

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <fcntl.h>
# include <string.h>
# include <limits.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <semaphore.h>
# include <signal.h>

typedef struct s_philos
{
	pthread_t	tid;
	int			id;
	int			check_eat;
	int			not_died;
	sem_t		*sem;
	sem_t		*sem_forks;
	sem_t		*sem_death;
	size_t		start_time;
	size_t		last_time_eat;
	size_t		time_eat;
	size_t		time_sleep;
	size_t		time_death;
	size_t		number_philos;
	int			number_eat;
	int			number_of_eat;
}	t_philos;

typedef struct s_process
{
	long		*pid;
	t_philos	*philo;
	sem_t		*sem_death;
	sem_t		*sem;
	sem_t		*sem_forks;
	size_t		start_time;
	size_t		time_eat;
	size_t		time_sleep;
	size_t		time_died;
	size_t		number_philos;
	int			number_eat;
}	t_process;

int		is_digit(char *s);
long	ft_atoi(const char *str);
size_t	get_time(void);
void	ft_usleep(size_t milliseconds);
int		check_death(t_philos *philo);
void	ft_routine(t_philos *philo);
void	*monitoring(void *philo);
int		check_number_of_eat(t_philos *philo);
void	create_philos(t_process *process);
void	print_message(int id, size_t start_time, char *mssg);

#endif