/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_number.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:11:20 by bazaluga          #+#    #+#             */
/*   Updated: 2024/11/04 17:19:24 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	num_len(long long n)
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
#include <stdio.h>
#include <limits.h>
int	write_number(long long n)
{
	printf("%lld\n", LLONG_MAX);
	printf("%d\n", num_len(LLONG_MAX));
	(void)n;
	return (0);
}
