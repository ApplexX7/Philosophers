/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_help.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:42:05 by mohilali          #+#    #+#             */
/*   Updated: 2024/02/12 18:10:40 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	speacial_case(t_philos *philos)
{
	ft_take_fork(philos);
	pthread_mutex_unlock(philos->r_fork);
	ft_usleep(philos->time_death);
}

int	death_loop(t_philos *philo)
{
	pthread_mutex_lock(philo->print);
	if (philo->finish_eat == 1 || *(philo->died) == 1)
	{
		pthread_mutex_unlock(philo->print);
		return (0);
	}
	pthread_mutex_unlock(philo->print);
	return (1);
}

void	wait_threads(t_threads *thread)
{
	int	i;

	i = 0;
	while (i < thread->number_philos)
	{
		if (pthread_join(thread->philos[i].tid, NULL) != 0)
			return ;
		i++;
	}
}

int	create_observe(pthread_t *observe, t_threads *thread)
{
	if (pthread_create(observe, NULL, monitoring, thread) != 0)
	{
		printf("Error: can't create philos\n");
		return (0);
	}
	if (pthread_detach(*observe) != 0)
	{
		printf("Error : can't deatch philos\n");
		return (0);
	}
	return (1);
}
