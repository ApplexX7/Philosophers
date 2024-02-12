/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus_fork.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:07:53 by mohilali          #+#    #+#             */
/*   Updated: 2024/02/12 12:34:36 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	fork_philos(t_process	*process, int i)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		(printf("Error : failed to fork a child"), exit(0));
	if (pid == 0)
	{
		if (pthread_create(&process->philo[i].tid, NULL,
				monitoring, &process->philo[i]) != 0)
			exit(0);
		pthread_detach(process->philo[i].tid);
		ft_routine(&process->philo[i]);
	}
	process->pid[i] = pid;
}

void	update_info(t_process *process, int i)
{
	process->philo[i].id = i + 1;
	process->philo[i].not_died = 0;
	process->philo[i].check_eat = 1;
	process->philo[i].number_of_eat = 0;
	process->philo[i].last_time_eat = get_time();
	process->philo[i].start_time = process->start_time;
	process->philo[i].time_death = process->time_died;
	process->philo[i].time_eat = process->time_eat;
	process->philo[i].time_sleep = process->time_sleep;
	process->philo[i].sem = process->sem;
	process->philo[i].sem_forks = process->sem_forks;
	process->philo[i].sem_death = process->sem_death;
	process->philo[i].number_philos = process->number_philos;
	process->philo[i].number_eat = process->number_eat;
}

void	create_philos(t_process *process)
{
	size_t	i;

	i = 0;
	process->philo = malloc(sizeof(t_philos) * (process->number_philos + 1));
	if (!process->philo)
		(printf("malloc faild!!"), exit(0));
	process->start_time = get_time();
	while (i < process->number_philos)
	{
		update_info(process, i);
		fork_philos(process, i);
		i++;
	}
}
