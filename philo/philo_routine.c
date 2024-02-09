/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 09:24:56 by mohilali          #+#    #+#             */
/*   Updated: 2024/02/07 18:20:00 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_thinking(t_philo	philo)
{
	pthread_mutex_lock(philo.print);
	ft_print_message(philo.id, philo.start_time,
		"is thinking\n", *(philo.died));
	pthread_mutex_unlock(philo.print);
}

void	ft_sleeping(t_philo	philo)
{
	pthread_mutex_lock(philo.print);
	ft_print_message(philo.id, philo.start_time,
		"is sleeping\n", *(philo.died));
	pthread_mutex_unlock(philo.print);
	ft_usleep(philo.time_to_sleep);
}

void	ft_eating(t_philo	*philo)
{
	pthread_mutex_lock(philo->r_fork);
	if (philo->number_of_philos == 1)
	{
		ft_take_fork(*philo);
		ft_usleep(philo->time_to_die);
		pthread_mutex_unlock(philo->r_fork);
		return ;
	}
	ft_take_fork(*philo);
	pthread_mutex_lock(philo->l_fork);
	ft_take_fork(*philo);
	pthread_mutex_lock(philo->deadlock);
	philo->last_eat = get_time();
	pthread_mutex_unlock(philo->deadlock);
	pthread_mutex_lock(philo->print);
	ft_print_message(philo->id, philo->start_time,
		"is eating\n", *(philo->died));
	pthread_mutex_unlock(philo->print);
	ft_usleep(philo->time_to_eat);
	philo->eating++;
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	number_of_eat(philo);
}

void	*routine(void *philo)
{
	t_philo	*philos;

	philos = (t_philo *)philo;
	if (philos->id % 2 != 0)
		ft_thinking(*philos);
	if (philos->id % 2 == 0)
	{
		ft_thinking(*philos);
		ft_usleep(philos->time_to_eat);
	}
	while (dead_loop(philos) == 1)
	{
		ft_eating(philos);
		ft_sleeping(*philos);
		ft_thinking(*philos);
	}
	*(philos->exit) += 1;
	return (NULL);
}
