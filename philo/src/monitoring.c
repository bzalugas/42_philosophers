/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:50:50 by bazaluga          #+#    #+#             */
/*   Updated: 2024/11/04 17:14:43 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_timestamp(void)
{
	long long		res;
	struct timeval	tv;

	if (gettimeofday(&tv,NULL))
		return (-1);
	res = 0;
	res = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (res);
}

void	*monitoring(void *data)
{
	long long	timestamp;
	t_table		*t;
	int			i;

	t = (t_table *)data;
	i = -1;
	while(++i < t->n_philos)
	{
		timestamp = get_timestamp();
		if (t->philos[i].state != EATING
			&& timestamp - t->philos[i].last_meal > t->die_time)
		{
			t->dead = true;
			pthread_mutex_lock(&t->philos[i].wr_state);
			t->philos[i].state = DEAD;
			pthread_mutex_unlock(&t->philos[i].wr_state);

		}
	}
	return (NULL);
}
