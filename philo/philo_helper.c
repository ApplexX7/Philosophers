/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 09:22:20 by mohilali          #+#    #+#             */
/*   Updated: 2024/02/10 14:54:21 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	number_of_eat(t_philo *philo)
{
	int number_of_eat;

	pthread_mutex_lock(philo->deadlock);
	number_of_eat = philo->eating;
	pthread_mutex_unlock(philo->deadlock);

	if (philo->number_of_eat == number_of_eat)
	{
		pthread_mutex_lock(philo->mutex);
		philo->not_died = 1;
		pthread_mutex_unlock(philo->mutex);
		return (1);
	}
	return (0);
}

size_t	get_time(void)
{
	struct timeval	currenttime;

	gettimeofday(&currenttime, NULL);
	return ((currenttime.tv_sec * 1000 + currenttime.tv_usec / 1000));
}

void	ft_print_message(int id, size_t start_time, char *message, int died)
{
	if (died == 0)
		printf("%lu %d %s", get_time() - start_time, id, message);
}

void	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_time();
	while (get_time() - start < milliseconds)
		usleep(500);
}

void	ft_take_fork(t_philo philo)
{
	pthread_mutex_lock(philo.print);
	ft_print_message(philo.id, philo.start_time,
		"has taken a fork\n", *(philo.died));
	pthread_mutex_unlock(philo.print);
}
