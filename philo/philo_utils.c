/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 19:16:04 by mohilali          #+#    #+#             */
/*   Updated: 2024/02/05 12:21:28 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atoi(const char *str)
{
	char	*s;
	int		sign;
	long	nbr;

	sign = 1;
	s = (char *) str;
	while (*s == ' ' || *s == '\n' || *s == '\v' || *s == '\f'
		|| *s == '\t' || *s == '\r')
		s++;
	if (*s == '+')
		s++;
	else if (*s == '-')
	{
		sign = -1;
		s++;
	}
	nbr = 0;
	while (*s >= '0' && *s <= '9' && nbr <= (long) INT_MAX + 1)
	{
		nbr = nbr * 10 + (*s - '0');
		s++;
	}
	return (nbr * sign);
}

int	is_digit(char *s)
{
	while (*s != '\0')
	{
		if ((*s < 48 || *s > 57) && *s != '+')
			return (0);
		s++;
	}
	return (1);
}
