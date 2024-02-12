/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 09:39:51 by mohilali          #+#    #+#             */
/*   Updated: 2024/02/10 17:00:02 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_died(int id, size_t start_time)
{
	printf("%lu %d died\n", get_time() - start_time, id);
}

int	dead_loop(t_philo *philo)
{
	int	*dead;

	pthread_mutex_lock(philo->print);
	dead = philo->died;
	pthread_mutex_unlock(philo->print);
	if (*dead == 1 || number_of_eat(philo) == 1)
		return (0);
	return (1);
}

int	check_philos_dead(t_philo philo)
{
	size_t	last_time_to_eat;

	pthread_mutex_lock(philo.deadlock);
	last_time_to_eat = philo.last_eat;
	pthread_mutex_unlock(philo.deadlock);
	if ((unsigned long)philo.time_to_die <= get_time() - last_time_to_eat)
		return (1);
	return (0);
}

static void	apply_death(t_threads *threads, int i)
{
	pthread_mutex_lock(threads->philo[i].print);
	threads->died = 1;
	print_died(threads->philo[i].id, threads->philo[i].start_time);
	pthread_mutex_unlock(threads->philo[i].print);
}

void	*monitoring(void *thread)
{
	int			i;
	t_threads	*threads;

	i = 0;
	threads = (t_threads *)thread;
	while (1)
	{
		if (check_philos_dead(threads->philo[i])
			&& !number_of_eat(&threads->philo[i]))
		{
			apply_death(threads, i);
			break ;
		}
		pthread_mutex_lock(threads->philo[i].protect);
		if (threads->exit == threads->number_of_philo)
		{
			pthread_mutex_unlock(threads->philo[i].protect);
			break ;
		}
		pthread_mutex_unlock(threads->philo[i].protect);
		if (i++ >= threads->philo[0].number_of_philos - 1)
			i = 0;
	}
	return (NULL);
}
