/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 19:01:32 by mohilali          #+#    #+#             */
/*   Updated: 2024/02/09 15:54:59 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
#define PHILO_BONUS_H

#define SEM_FORKS "/sem_forks"
#define SEM_PRINT "/sem_print"
#define SEM_KILL "/sem_kill"
#define SEM_PROTECT "/sem_protc"

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <fcntl.h>
# include <string.h>
# include <limits.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>

typedef struct s_philos
{
	pthread_t	tid;
	pthread_mutex_t mutex;
	sem_t		*forks;
	sem_t		*print;
	sem_t		*kill;
	sem_t		*protec;
	int 		time_to_eat;
	int 		id;
	int 		died;
	int 		time_to_sleep;
	int 		time_to_die;
	int 		number_of_philos;
	int 		number_of_eats;
	size_t		start_time;
	int			eating;
	size_t		last_eat;

}   t_philos;


typedef struct s_process
{
	t_philos	*philo;
	sem_t		*forks;
	sem_t		*print;
	sem_t		*kill;
	int			id;
	int 		time_to_sleep;
	int 		time_to_die;
	int			time_to_eat;
	int 		number_of_philos;
	int 		number_of_eats;
	long		*pid;

} t_process;

int	is_digit(char *s);
long	ft_atoi(const char *str);
void	*create_philos(t_philos *philos, t_process *main_process);
void	*monitoring(void *philo);
void	routine(t_philos *philos);
void	ft_print_message(t_philos *philo,int id, size_t start_time, char *message);
void	create_threads(t_process *philos);
void	routine(t_philos *philos);
size_t	get_time(void);
void	ft_usleep(size_t milliseconds);
int check_death(t_philos *philos);
int	exit_loop(t_philos *philos);
int	check_eating(t_philos *philos);

#endif