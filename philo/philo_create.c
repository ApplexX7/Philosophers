/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_create.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 09:47:40 by mohilali          #+#    #+#             */
/*   Updated: 2024/02/07 18:18:54 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_destroy_mutex(t_threads *threads)
{
	int	i;

	i = 0;
	while (i < threads->number_of_philo)
	{
		pthread_mutex_destroy(&threads->forks[i]);
		i++;
	}
}

int	ft_create_observe(pthread_t *observer, t_threads *threads)
{
	if (pthread_create(observer, NULL, monitoring, threads) != 0)
		return (0);
	return (1);
}

void	philo_info(t_threads *threads, int i, int id, long start)
{
	threads->philo[i].id = id;
	threads->philo[i].exit = &threads->exit;
	threads->philo[i].eating = 0;
	threads->philo[i].not_died = 0;
	threads->philo[i].start_time = start;
	threads->philo[i].died = &threads->died;
	threads->philo[i].last_eat = get_time();
	threads->philo[i].number_of_philos = threads->number_of_philo;
	threads->philo[i].time_to_eat = threads->time_to_eat;
	threads->philo[i].time_to_die = threads->time_to_die;
	threads->philo[i].time_to_sleep = threads->time_to_sleep;
	threads->philo[i].r_fork = &threads->forks[i];
	threads->philo[i].deadlock = &threads->deadlock;
	threads->philo[i].print = &threads->print;
	threads->philo[i].mutex = &threads->mutex;
	threads->philo[i].number_of_eat = threads->number_of_eats;
	if (i == threads->number_of_philo - 1)
		threads->philo[i].l_fork = &threads->forks[0];
	else
		threads->philo[i].l_fork = &threads->forks[i + 1];
}

static int	init_philos(t_threads *threads)
{
	int		i;
	int		id;
	long	start;

	i = 0;
	id = 1;
	start = get_time();
	while (i < threads->number_of_philo)
	{
		philo_info(threads, i, id, start);
		if (pthread_create(&threads->philo[i].tid, NULL, routine,
				&threads->philo[i]) != 0)
			return (0);
		id++;
		i++;
	}
	return (1);
}

void	create_philos(t_threads *threads)
{
	int			i;
	pthread_t	observe;

	threads->philo = malloc(sizeof(t_philo) * threads->number_of_philo);
	if (!threads->philo)
		return ;
	if (!init_philos(threads))
		return ;
	i = 0;
	if (!ft_create_observe(&observe, threads))
		return ;
	if (pthread_join(observe, NULL) != 0)
		return ;
	while (i < threads->number_of_philo)
	{
		if (pthread_join(threads->philo[i].tid, NULL) != 0)
			return ;
		i++;
	}
	ft_destroy_mutex(threads);
}
