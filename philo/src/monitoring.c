/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:50:50 by bazaluga          #+#    #+#             */
/*   Updated: 2024/11/07 13:51:28 by bazaluga         ###   ########.fr       */
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

	t->start_time = get_timestamp();
	pthread_mutex_unlock(&t->go);
	while (!t->dead)
	{
		i = -1;
		while(++i < t->n_philos && !t->dead)
		{
			timestamp = get_timestamp();
			if (t->philos[i].state != EATING
				&& t->philos[i].last_meal && timestamp - t->philos[i].last_meal >= t->die_time)
			{
				pthread_mutex_lock(&t->fdout);
				write_dead(i + 1, timestamp - t->start_time);
				pthread_mutex_unlock(&t->fdout);
				pthread_mutex_lock(&t->dead_lock);
				t->dead = true;
				pthread_mutex_unlock(&t->dead_lock);
				pthread_mutex_lock(&t->philos[i].wr_state);
				t->philos[i].state = DEAD;
				pthread_mutex_unlock(&t->philos[i].wr_state);
			}
		}
	}
	return (t->dead); // diff return if dead or max_meal
}
