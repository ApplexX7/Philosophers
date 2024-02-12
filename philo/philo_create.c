/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_create.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:45:03 by mohilali          #+#    #+#             */
/*   Updated: 2024/02/12 18:31:48 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	update_info(t_threads *thread, int i)
{
	thread->philos[i].id = i + 1;
	thread->philos[i].died = &thread->died;
	thread->philos[i].finish_eat = 0;
	thread->philos[i].check_eat = 1;
	thread->philos[i].print = &thread->print;
	thread->philos[i].mutex = &thread->mutex;
	thread->philos[i].start_time = thread->start_time;
	thread->philos[i].last_time_eat = get_time();
	thread->philos[i].time_death = thread->time_died;
	thread->philos[i].time_eat = thread->time_eat;
	thread->philos[i].time_sleep = thread->time_sleep;
	thread->philos[i].number_eat = thread->number_eat;
	thread->philos[i].number_philos = thread->number_philos;
	thread->philos[i].r_fork = &thread->forks[i];
	if (i == thread->number_philos - 1)
		thread->philos[i].l_fork = &thread->forks[0];
	else
		thread->philos[i].l_fork = &thread->forks[i + 1];
}

int	create_forks(t_threads *thread)
{
	int	i;

	i = 0;
	thread->forks = malloc(sizeof(pthread_mutex_t) * thread->number_philos);
	if (!thread->forks)
	{
		printf("Error : malloc failed\n");
		return (1);
	}
	while (i < thread->number_philos)
	{
		if (pthread_mutex_init(&thread->forks[i], NULL) != 0)
		{
			printf("Error : can't create forks\n");
			return (1);
		}
		i++;
	}
	pthread_mutex_init(&thread->mutex, NULL);
	pthread_mutex_init(&thread->print, NULL);
	return (0);
}

void	create_threads(t_threads *thread)
{
	int			i;
	pthread_t	observe;

	i = 0;
	thread->philos = malloc(sizeof(t_philos) * thread->number_philos);
	if (!thread->philos)
	{
		printf("Error : malloc failed\n");
		return ;
	}
	thread->start_time = get_time();
	while (i < thread->number_philos)
	{
		update_info(thread, i);
		if (pthread_create(&thread->philos[i].tid, NULL,
				ft_routine, &thread->philos[i]) != 0)
		{
			printf("Error : can't create threads\n");
			return ;
		}
		i++;
	}
	if (!create_observe(&observe, thread))
		return ;
	wait_threads(thread);
}
