/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:50:50 by bazaluga          #+#    #+#             */
/*   Updated: 2024/11/08 12:48:46 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

long long	get_timestamp(pthread_mutex_t *mutex)
{
	long long		res;
	struct timeval	tv;

	if (mutex)
		pthread_mutex_lock(mutex);
	if (gettimeofday(&tv, NULL))
		return (-1);
	res = 0;
	res = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	if (mutex)
		pthread_mutex_unlock(mutex);
	return (res);
}

static bool	is_starving(t_philo *p, long long timestamp)
{
	bool	check;

	pthread_mutex_lock(&p->wr_state);
	check = p->state != EATING;
	pthread_mutex_unlock(&p->wr_state);
	pthread_mutex_lock(&p->wr_last_meal);
	check = check && (timestamp - p->last_meal >= p->table->die_time);
	pthread_mutex_unlock(&p->wr_last_meal);
	return (check);
}

static bool	philo_ended(t_philo *p)
{
	bool	check;

	pthread_mutex_lock(&p->wr_state);
	check = p->state == ENDED;
	pthread_mutex_unlock(&p->wr_state);
	return (check);
}

int	monitoring(t_table *t)
{
	long long	timestamp;
	int			i;

	while (!t->dead)
	{
		i = -1;
		while (++i < t->n_philos && !t->dead)
		{
			timestamp = get_timestamp(NULL);
			if (!philo_ended(&t->philos[i])
				&& is_starving(&t->philos[i], timestamp))
			{
				print_state(&t->philos[i], timestamp - t->start_time, true);
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
