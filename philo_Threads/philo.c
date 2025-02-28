/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 14:00:03 by mohilali          #+#    #+#             */
/*   Updated: 2024/02/12 18:33:17 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse_input(char **av, t_threads *thread)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (!is_digit(av[i]))
			return (1);
		i++;
	}
	thread->number_philos = ft_atoi(av[1]);
	thread->time_died = ft_atoi(av[2]);
	thread->time_eat = ft_atoi(av[3]);
	thread->time_sleep = ft_atoi(av[4]);
	if (av[5])
		thread->number_eat = ft_atoi(av[5]);
	else
		thread->number_eat = -1;
	return (0);
}

void	destroy_mutex(t_threads *thread)
{
	int	i;

	i = 0;
	while (i < thread->number_philos)
	{
		pthread_mutex_destroy(&thread->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&thread->print);
	pthread_mutex_destroy(&thread->mutex);
}

int	main(int ac, char **av)
{
	t_threads	*thread;

	if (ac == 5 || ac == 6)
	{
		thread = malloc(sizeof(t_threads));
		if (!thread)
			return (0);
		if (parse_input(av, thread))
		{
			free(thread);
			return (0);
		}
		if (create_forks(thread))
			return (0);
		create_threads(thread);
		destroy_mutex(thread);
		free(thread->forks);
		free(thread->philos);
		free(thread);
	}
	else
		printf("Invalid input\n");
}
