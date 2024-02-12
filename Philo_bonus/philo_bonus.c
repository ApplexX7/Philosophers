/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 15:09:23 by mohilali          #+#    #+#             */
/*   Updated: 2024/02/12 12:28:35 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	destroy_semaphore(t_process *process)
{
	if (sem_close(process->sem) != 0)
		(printf("error in closing semaphore"), exit(0));
	if (sem_close(process->sem_death) != 0)
		(printf("error in closing semaphore"), exit(0));
	if (sem_close(process->sem_forks) != 0)
		(printf("error in closing semaphore"), exit(0));
	if (sem_unlink(SEM_AMPHORE) != 0)
		(printf("error in unlink semaphore"), exit(0));
	if (sem_unlink(SEM_FORKS) != 0)
		(printf("error in unlink semaphore"), exit(0));
	if (sem_unlink(SEM_DEATH) != 0)
		(printf("error in unlink semaphore"), exit(0));
}

void	open_semaphore(t_process *process)
{
	sem_unlink(SEM_AMPHORE);
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_DEATH);
	process->sem = sem_open(SEM_AMPHORE, O_CREAT | O_EXCL, 0644, 1);
	if (process->sem == SEM_FAILED)
		(printf("Error : can't open semaphore"), exit(0));
	process->sem_forks = sem_open(SEM_FORKS, O_CREAT | O_EXCL,
			0644, process->number_philos);
	if (process->sem_forks == SEM_FAILED)
		(printf("Error : can't open semaphore"), exit(0));
	process->sem_death = sem_open(SEM_DEATH, O_CREAT | O_EXCL, 0644, 1);
	if (process->sem_death == SEM_FAILED)
		(printf("Error : can't open semaphore"), exit(0)), exit(0);
}

int	parse_input(char **av, t_process *process)
{
	int	i;

	i = 0;
	while (av[i])
	{
		if (!is_digit(av[i]))
			return (1);
		i++;
	}
	process->number_philos = ft_atoi(av[1]);
	process->time_died = ft_atoi(av[2]);
	process->time_eat = ft_atoi(av[3]);
	process->time_sleep = ft_atoi(av[4]);
	if (av[5])
		process->number_eat = ft_atoi(av[5]);
	else
		process->number_eat = -1;
	process->pid = malloc(sizeof(long) * process->number_philos);
	if (!process->pid)
		(printf("Error: in malloc"), exit(0));
	return (0);
}

void	wait_philos(t_process *process)
{
	int		status;
	size_t	i;

	i = 0;
	while (1)
	{
		if (waitpid(-1, &status, 0) == -1)
			break ;
		if (status >> 8 == 20)
		{
			while (i < process->number_philos)
			{
				kill(process->pid[i], SIGKILL);
				i++;
			}
			break ;
		}
	}
}

int	main(int ac, char **av)
{
	t_process	*process;

	if (ac == 5 || ac == 6)
	{
		process = malloc(sizeof(t_process));
		if (parse_input(av, process))
			(printf("not a valid arguments"), exit(0));
		open_semaphore(process);
		create_philos(process);
		wait_philos(process);
		destroy_semaphore(process);
		free(process->pid);
		free(process->philo);
		free(process);
	}
	else
		printf("not a valid argument!!\n");
	return (0);
}
