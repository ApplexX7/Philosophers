/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:59:46 by mohilali          #+#    #+#             */
/*   Updated: 2025/02/28 15:27:09 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_take_fork(t_philos *philo)
{
	sem_wait(philo->sem);
	print_message(philo->id, philo->start_time, FORKS);
	sem_post(philo->sem);
}

void	ft_thinking(t_philos *philo)
{
	sem_wait(philo->sem);
	print_message(philo->id, philo->start_time, THINK);
	sem_post(philo->sem);
}

void	ft_sleeping(t_philos *philo)
{
	sem_wait(philo->sem);
	print_message(philo->id, philo->start_time, SLEEP);
	sem_post(philo->sem);
	ft_usleep(philo->time_sleep);
}

void	ft_eating(t_philos *philo)
{
	sem_wait(philo->sem_forks);
	ft_take_fork(philo);
	sem_wait(philo->sem_forks);
	ft_take_fork(philo);
	sem_wait(philo->sem_death);
	if (philo->number_eat != 0)
		philo->last_time_eat = get_time();
	philo->number_of_eat++;
	sem_post(philo->sem_death);
	sem_wait(philo->sem);
	philo->check_eat = 0;
	if (philo->number_eat != 0)
		print_message(philo->id, philo->start_time, EATING);
	if (philo->number_of_eat >= philo->number_eat && philo->number_eat > 0)
		philo->not_died = 1;
	philo->check_eat = 1;
	sem_post(philo->sem);
	ft_usleep(philo->time_eat);
	sem_post(philo->sem_forks);
	sem_post(philo->sem_forks);
}

void	ft_routine(t_philos *philo)
{
	while (check_number_of_eat(philo))
	{
		ft_eating(philo);
		ft_sleeping(philo);
		ft_thinking(philo);
	}
}
