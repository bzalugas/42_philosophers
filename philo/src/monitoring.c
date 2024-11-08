/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:50:50 by bazaluga          #+#    #+#             */
/*   Updated: 2024/11/08 11:18:56 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

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

int	monitoring(t_table *t)
{
	long long	timestamp;
	int			i;

	while (!t->dead)
	{
		i = -1;
		while(++i < t->n_philos && !t->dead)
		{
			timestamp = get_timestamp();
			if (is_starving(&t->philos[i], timestamp))
			{
				print_state(&t->philos[i], timestamp - t->start_time, true);
				pthread_mutex_lock(&t->dead_lock);
				t->dead = true;
				pthread_mutex_unlock(&t->dead_lock);
				/* pthread_mutex_lock(&t->philos[i].wr_state); */
				/* t->philos[i].state = DEAD; */
				/* pthread_mutex_unlock(&t->philos[i].wr_state); */
			}
		}
	}
	return (t->dead); // diff return if dead or max_meal
}
