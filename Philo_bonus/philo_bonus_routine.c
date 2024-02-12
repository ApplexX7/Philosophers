/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus_routine.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 13:54:32 by mohilali          #+#    #+#             */
/*   Updated: 2024/02/09 20:29:32 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"


void	ft_thinking(t_philos	*philo)
{
	ft_print_message(philo,philo->id, philo->start_time,
		"is thinking\n");
}

void	ft_take_fork(t_philos *philo)
{
	ft_print_message(philo ,philo->id, philo->start_time,
		"has taken a fork\n");
}

void	ft_sleeping(t_philos	*philos)
{
	ft_print_message(philos ,philos->id, philos->start_time,
		"is sleeping\n");
	ft_usleep(philos->time_to_sleep);
}

void	ft_eating(t_philos *philos)
{
	sem_wait(philos->forks);
	if (philos->number_of_philos == 1)
	{
		ft_take_fork(philos);
		sem_post(philos->forks);
		ft_usleep(philos->time_to_die);
		ft_print_message(philos ,philos->id, philos->start_time, "died\n");
		exit(0);
	}
	ft_take_fork(philos);
	sem_wait(philos->forks);
	ft_take_fork(philos);
	ft_print_message(philos ,philos->id, philos->start_time,
		"is eating\n");
	sem_wait(philos->protec);
	philos->last_eat = get_time();
	sem_post(philos->protec);
	philos->eating++;
	ft_usleep(philos->time_to_eat);
	sem_post(philos->forks);
	sem_post(philos->forks);
}

void	routine(t_philos *philos)
{
	ft_thinking(philos);
	while(exit_loop(philos))
	{
		ft_eating(philos);
		ft_sleeping(philos);
		ft_thinking(philos);
	}
	exit(0);
}
