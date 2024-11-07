/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_number.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:11:20 by bazaluga          #+#    #+#             */
/*   Updated: 2024/11/07 09:17:45 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	num_len(unsigned long long n)
{
	int	len;

	len = 0;
	while (n)
	{
		len++;
		n /= 10;
	}
	return (len + (len == 0));
}

int	write_number(unsigned long long n, bool space)
{
	char	str_nb[22];
	int		len;
	int		i;

	if (n < 10)
	{
		str_nb[0] = n + '0';
		str_nb[1] = ' ';
		write(STDOUT_FILENO, str_nb, 1 + space);
		return (0);
	}
	len = num_len(n);
	str_nb[len] = ' ';
	i = len - 1;
	while (n > 0)
	{
		str_nb[i--] = (n % 10) + '0';
		n /= 10;
	}
	write(STDOUT_FILENO, str_nb, len + space);
	return (0);
}
