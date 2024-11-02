/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 11:36:25 by bazaluga          #+#    #+#             */
/*   Updated: 2024/11/02 16:38:03 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isspace(int c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

static int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_atoi(const char *nptr)
{
	unsigned int	n;
	int				sign;
	size_t			i;

	if (!nptr)
		return (0);
	i = 0;
	while (nptr[i] && ft_isspace(nptr[i]))
		i++;
	sign = 1;
	if (nptr[i] && (nptr[i] == '-' || nptr[i] == '+'))
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	n = 0;
	while (nptr[i] && ft_isdigit(nptr[i]))
	{
		n = n * 10 + (nptr[i] - '0');
		i++;
	}
	return (n * sign);
}
