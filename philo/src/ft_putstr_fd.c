/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 18:15:13 by bazaluga          #+#    #+#             */
/*   Updated: 2024/11/12 13:12:24 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_putstr_fd(const char *s, int fd)
{
	ssize_t	len;
	ssize_t	res;

	if (!s)
		return (0);
	len = 0;
	while (s[len])
		len++;
	res = write(fd, s, len);
	if (res < len)
		return (0);
	return (1);
}
