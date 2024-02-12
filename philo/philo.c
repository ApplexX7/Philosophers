/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 14:03:12 by mohilali          #+#    #+#             */
/*   Updated: 2024/02/10 17:11:52 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_time(t_threads *trea, char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (!is_digit(av[i]))
			return (1);
		i++;
	}
	pthread_mutex_init(&trea->print, NULL);
	pthread_mutex_init(&trea->deadlock, NULL);
	pthread_mutex_init(&trea->mutex, NULL);
	pthread_mutex_init(&trea->protect, NULL);
	trea->exit = 0;
	trea->number_of_philo = ft_atoi(av[1]);
	trea->time_to_die = ft_atoi(av[2]);
	trea->time_to_eat = ft_atoi(av[3]);
	trea->time_to_sleep = ft_atoi(av[4]);
	trea->died = 0;
	if (av[5])
		trea->number_of_eats = ft_atoi(av[5]);
	else
		trea->number_of_eats = -1;
	return (0);
}

int	init_forks(t_threads *trea)
{
	int	i;

	trea->forks = malloc(sizeof(pthread_mutex_t) * trea->number_of_philo);
	if (!trea->forks)
		return (1);
	i = 0;
	while (i < trea->number_of_philo)
	{
		if (pthread_mutex_init(&trea->forks[i], NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_threads	*trea;

	if (ac == 5 || ac == 6)
	{
		trea = malloc(sizeof(t_threads));
		if (!trea)
			return (0);
		if (init_time(trea, av))
			return (free(trea), 0);
		if (init_forks(trea))
			return (free(trea), 0);
		create_philos(trea);
		pthread_mutex_destroy(&trea->deadlock);
		pthread_mutex_destroy(&trea->protect);
		pthread_mutex_destroy(&trea->mutex);
		pthread_mutex_destroy(&trea->print);
		free(trea->philo);
		free(trea->forks);
		free(trea);
	}
	else
		write(1, "Input error\n", 12);
}
