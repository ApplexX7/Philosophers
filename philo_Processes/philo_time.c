/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 15:55:13 by mohilali          #+#    #+#             */
/*   Updated: 2025/02/28 15:27:14 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
