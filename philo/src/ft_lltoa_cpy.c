/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lltoa_cpy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:53:32 by bazaluga          #+#    #+#             */
/*   Updated: 2024/11/12 13:12:35 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static size_t	int_size(long n)
{
	size_t	size;

	size = 1;
	while (n > 9)
	{
		size++;
		n /= 10;
	}
	return (size);
}

char	*ft_lltoa_cpy(long long n, char *nb)
{
	long	n2;
	int		neg;
	size_t	size;
	char	*ret;

	n2 = n;
	neg = 0;
	if (n2 < 0 && ++neg)
		n2 *= -1;
	size = int_size(n2);
	ret = &nb[size];
	ret[0] = 0;
	size += neg;
	while (size > 0)
	{
		nb[size - 1] = n2 % 10 + '0';
		n2 /= 10;
		size--;
	}
	if (neg)
		nb[0] = '-';
	return (ret);
}
