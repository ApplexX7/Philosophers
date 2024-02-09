/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 09:39:51 by mohilali          #+#    #+#             */
/*   Updated: 2024/02/09 19:20:15 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_died(int id, size_t start_time)
{
	printf("%lu %d died\n", get_time() - start_time, id);
}

int	dead_loop(t_philo *philo)
{
	if (*philo->died == 1 || number_of_eat(philo) == 1)
		return (0);
	return (1);
}

int	check_philos_dead(t_philo philo)
{
	if ((unsigned long)philo.time_to_die <= get_time() - philo.last_eat)
		return (1);
	return (0);
}

void	*monitoring(void *thread)
{
	int			i;
	t_threads	*threads;

	i = 0;
	threads = (t_threads *)thread;
	while (1)
	{
		pthread_mutex_lock(threads->philo[i].mutex);
		threads->not_died = threads->philo[i].not_died;
		pthread_mutex_unlock(threads->philo[i].mutex);
		if (check_philos_dead(threads->philo[i]) == 1 && !number_of_eat(&threads->philo[i]))
		{
			pthread_mutex_lock(threads->philo[i].print);
			threads->died = 1;
			pthread_mutex_unlock(threads->philo[i].print);
			print_died(threads->philo[i].id, threads->philo[i].start_time);
			break ;
		}
		if(threads->exit == threads->number_of_philo)
			break;
		if (i++ >= threads->philo[0].number_of_philos - 1)
			i = 0;
	}
	return (NULL);
}
