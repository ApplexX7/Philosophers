/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 19:01:18 by mohilali          #+#    #+#             */
/*   Updated: 2024/02/09 15:56:15 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"


int	exit_loop(t_philos *philos)
{
	if ((philos->eating  >= philos->number_of_eats && philos->number_of_eats >= 0) || philos->died == 1)
		return (0);
	return (1);
}

int	check_eating(t_philos *philos)
{
	if (philos->eating >= philos->number_of_eats && philos->number_of_eats != -1)
		return (1);
	return 0;
}

void	*monitoring(void *philo)
{
	t_philos *philos;
	philos = (t_philos *)philo;

	while (1)
	{
		if (check_death(philos) && !check_eating(philos))
		{
			sem_post(philos->kill);
			sem_wait(philos->print);
			printf("%lu %d died\n", get_time() - philos->start_time, philos->id);
			philos->died = 1;
			sem_unlink(SEM_PROTECT);
			exit(0);
		}
	}
	return NULL;
}


int	init_time(t_process *philos, char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (!is_digit(av[i]))
			return (1);
		i++;
	}
	philos->id = 0;
	philos->number_of_philos = ft_atoi(av[1]);
	philos->time_to_die = ft_atoi(av[2]);
	philos->time_to_eat = ft_atoi(av[3]);
	philos->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		philos->number_of_eats = ft_atoi(av[5]);
	else
		philos->number_of_eats = -1;
	philos->pid = malloc(sizeof(long) * philos->number_of_philos);
	if (!philos->pid)
		exit(0);
	return (0);
}

void init_forks(t_process *philos)
{
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_KILL);
	sem_unlink(SEM_PRINT);
	philos->forks = sem_open(SEM_FORKS, O_CREAT | O_EXCL, 0666, philos->number_of_philos);
	if (philos->forks == SEM_FAILED)
	{
		perror("sem_error:");
		exit(0);
	}
	philos->print = sem_open(SEM_PRINT, O_CREAT | O_EXCL, 0666, 1);
	if (philos->print == SEM_FAILED)
	{
		perror("sem_error:");
		exit(0);
	}
	philos->kill = sem_open(SEM_KILL, O_CREAT | O_EXCL , 0666, 0);
	if (philos->kill == SEM_FAILED)
	{
		perror("sem_error:");
		exit(0);
	}
}

void	*kill_philos(void *philo)
{
	t_process *philos = (t_process *) philo;
	int i = 0;

	sem_wait(philos->kill);
	while (i < philos->number_of_philos)
	{
		if (kill(philos->pid[i], SIGINT) != 0)
			perror("error");
		i++;
	}
	return (NULL);
}

void	ll()
{
	system("leaks philo_bonus");
}

int main(int ac, char **av)
{
	t_process *philos;
	pthread_t	observe;
	long i;
	
	if (ac == 5 || ac == 6)
	{
		// atexit(ll);
		philos = malloc(sizeof(t_process));
		if (init_time(philos, av))
			return (free(philos), 0);
		init_forks(philos);
		create_threads(philos);
		if (pthread_create(&observe, NULL, kill_philos, philos) != 0)
			exit(0);
		if (pthread_detach(observe) != 0)
			exit(0);
		i = 0;
		while (i < philos->pid[i])
		{
			waitpid(philos->pid[i], NULL, 0);
			i++;
		}
		free(philos->pid);
		free(philos->philo);
		free(philos);
		sem_unlink(SEM_FORKS);
		sem_unlink(SEM_KILL);
		sem_unlink(SEM_PRINT);
		// sem_close(philos->forks);
	}
}
