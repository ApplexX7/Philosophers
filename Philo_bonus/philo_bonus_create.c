/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus_create.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 12:20:25 by mohilali          #+#    #+#             */
/*   Updated: 2024/02/09 20:16:34 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"


void	*create_philos(t_philos *philos, t_process *main_process)
{
	main_process->pid[main_process->id] = fork();
	if (main_process->pid[main_process->id] == -1)
		exit(0);
	if (main_process->pid[main_process->id] == 0)
	{
		sem_unlink(SEM_PROTECT);
		philos->protec = sem_open(SEM_PROTECT, O_CREAT | O_EXCL, 0664, 1);
		if (philos->protec == SEM_FAILED)
			perror("error:"), exit(0);
		if (pthread_create(&philos->tid, NULL, monitoring, philos) != 0)
			perror("Error :"), exit(0);
		if (pthread_detach(philos->tid) != 0)
			perror("Error :"), exit(0);
		routine(philos);
	}
	main_process->id +=1;
	return NULL;
}

void	philo_info(t_process *threads, int i, int id, long start)
{
	threads->philo[i].died = 0;
	threads->philo[i].id = id;
	threads->philo[i].forks = threads->forks;
	threads->philo[i].print = threads->print;
	threads->philo[i].kill = threads->kill;
	threads->philo[i].eating = 0;
	threads->philo[i].start_time = start;
	threads->philo[i].last_eat = get_time();
	threads->philo[i].number_of_philos = threads->number_of_philos;
	threads->philo[i].time_to_eat = threads->time_to_eat;
	threads->philo[i].time_to_die = threads->time_to_die;
	threads->philo[i].time_to_sleep = threads->time_to_sleep;
	threads->philo[i].number_of_eats = threads->number_of_eats;
}

static int	init_philos(t_process *philos)
{
	int		i;
	int		id;
	long	start;

	i = 0;
	id = 1;
	start = get_time();
	while (i < philos->number_of_philos)
	{
		philo_info(philos, i, id, start);
		create_philos(&philos->philo[i], philos);
		id++;
		i++;
	}
	return (1);
}

void	create_threads(t_process *philos)
{

	philos->philo = malloc(sizeof(t_philos) *  philos->number_of_philos);
	if (!philos->philo)
		exit(0);
	if (!init_philos(philos))
		exit(0);
}
