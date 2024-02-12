/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:37:13 by mohilali          #+#    #+#             */
/*   Updated: 2024/02/12 18:57:51 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_think(t_philos *philos)
{
	pthread_mutex_lock(philos->print);
	if (*(philos->died) == 0)
		print_message(philos->id, philos->start_time, THINK);
	pthread_mutex_unlock(philos->print);
}

void	ft_take_fork(t_philos *philos)
{
	pthread_mutex_lock(philos->print);
	if (*(philos->died) == 0)
		print_message(philos->id, philos->start_time, FORKS);
	pthread_mutex_unlock(philos->print);
}

void	ft_sleep(t_philos *philos)
{
	pthread_mutex_lock(philos->print);
	if (*(philos->died) == 0)
		print_message(philos->id, philos->start_time, SLEEP);
	pthread_mutex_unlock(philos->print);
	ft_usleep(philos->time_sleep);
}

void	ft_eat(t_philos *philos)
{
	pthread_mutex_lock(philos->r_fork);
	if (philos->number_philos == 1)
	{
		speacial_case(philos);
		return ;
	}
	ft_take_fork(philos);
	pthread_mutex_lock(philos->l_fork);
	ft_take_fork(philos);
	pthread_mutex_lock(philos->mutex);
	if (philos->number_eat != 0)
		philos->last_time_eat = get_time();
	philos->number_of_eat++;
	pthread_mutex_unlock(philos->mutex);
	pthread_mutex_lock(philos->print);
	philos->check_eat = 0;
	if (*(philos->died) == 0 && philos->number_eat != 0)
		print_message(philos->id, philos->start_time, EATING);
	if (philos->number_of_eat >= philos->number_eat && philos->number_eat > 0)
		philos->finish_eat = 1;
	philos->check_eat = 1;
	pthread_mutex_unlock(philos->print);
	ft_usleep(philos->time_eat);
	pthread_mutex_unlock(philos->r_fork);
	pthread_mutex_unlock(philos->l_fork);
}

void	*ft_routine(void *thread_philos)
{
	t_philos	*philo;

	philo = (t_philos *)thread_philos;
	if (philo->id % 2 == 0)
	{
		ft_think(philo);
		ft_usleep(philo->time_eat);
	}
	while (death_loop(philo))
	{
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo);
	}
	return (NULL);
}
