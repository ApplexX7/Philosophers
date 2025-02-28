/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitoring.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:39:23 by mohilali          #+#    #+#             */
/*   Updated: 2024/02/12 18:57:31 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_philos *philos)
{
	pthread_mutex_lock(philos->mutex);
	if ((unsigned long)philos->time_death <= get_time() - philos->last_time_eat
		&& philos->finish_eat == 0)
	{
		pthread_mutex_unlock(philos->mutex);
		return (1);
	}
	pthread_mutex_unlock(philos->mutex);
	return (0);
}

void	apply_death(t_threads *threads, int i)
{
	pthread_mutex_lock(threads->philos[i].mutex);
	threads->died = 1;
	print_message(threads->philos[i].id, threads->philos[i].start_time, DEATH);
	pthread_mutex_unlock(threads->philos[i].mutex);
}

void	*monitoring(void *data)
{
	t_threads	*thread;
	int			i;

	i = 0;
	thread = (t_threads *) data;
	while (1)
	{
		pthread_mutex_lock(thread->philos[i].print);
		if (thread->philos[i].check_eat == 1 && check_death(&thread->philos[i]))
		{
			pthread_mutex_unlock(thread->philos[i].print);
			apply_death(thread, i);
			break ;
		}
		pthread_mutex_unlock(thread->philos[i].print);
		if (i++ >= thread->philos[0].number_philos - 1)
			i = 0;
	}
	return (NULL);
}
