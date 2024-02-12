/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 13:51:30 by mohilali          #+#    #+#             */
/*   Updated: 2024/02/09 13:53:00 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

size_t	get_time(void)
{
	struct timeval	currenttime;

	gettimeofday(&currenttime, NULL);
	return ((currenttime.tv_sec * 1000 + currenttime.tv_usec / 1000));
}
void	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_time();
	while (get_time() - start < milliseconds)
		usleep(500);
}

void	ft_print_message(t_philos *philo,int id, size_t start_time, char *message)
{
	sem_wait(philo->print);
	if (philo->died != 1)
		printf("%lu %d %s", get_time() - start_time, id, message);
	sem_post(philo->print);
}

int check_death(t_philos *philos)
{
	sem_wait(philos->protec);
	if ((unsigned long)philos->time_to_die <= get_time() - philos->last_eat)
	{
		sem_post(philos->protec);
		return 1;
	}
	sem_post(philos->protec);
	return 0;
}
