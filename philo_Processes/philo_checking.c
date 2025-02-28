/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_checking.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:03:38 by mohilali          #+#    #+#             */
/*   Updated: 2025/02/28 15:27:00 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_number_of_eat(t_philos *philo)
{
	sem_wait(philo->sem);
	if (philo->not_died == 1)
	{
		sem_post(philo->sem);
		exit(0);
	}
	sem_post(philo->sem);
	return (1);
}

int	check_death(t_philos *philo)
{
	sem_wait(philo->sem_death);
	if (philo->time_death <= get_time() - philo->last_time_eat)
	{
		sem_post(philo->sem_death);
		return (0);
	}
	sem_post(philo->sem_death);
	return (1);
}

void	*monitoring(void *philo)
{
	t_philos	*philos;

	philos = (t_philos *)philo;
	while (1)
	{
		sem_wait(philos->sem);
		if (philos->not_died == 1)
		{
			sem_post(philos->sem);
			return (NULL);
		}
		if (philos->check_eat == 1 && !check_death(philos))
		{
			print_message(philos->id, philos->start_time, DEATH);
			exit(20);
		}
		sem_post(philos->sem);
	}
	return (NULL);
}
