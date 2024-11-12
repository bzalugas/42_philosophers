/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:50:50 by bazaluga          #+#    #+#             */
/*   Updated: 2024/11/12 11:42:47 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stdbool.h>

long long	get_timestamp(pthread_mutex_t *mutex, long long *var)
{
	long long		res;
	struct timeval	tv;

	if (mutex)
		pthread_mutex_lock(mutex);
	if (gettimeofday(&tv, NULL))
		return (*var = -1, -1);
	res = 0;
	res = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	if (var)
		*var = res;
	if (mutex)
		pthread_mutex_unlock(mutex);
	return (res);
}

static bool	is_starving(t_philo *p, long long timestamp)
{
	bool	check;

	check = false;
	pthread_mutex_lock(&p->wr_state);
	if (p->state != EATING)
	{
		pthread_mutex_unlock(&p->wr_state);
		pthread_mutex_lock(&p->wr_last_meal);
		if (timestamp - p->last_meal >= p->table->die_time)
			return (pthread_mutex_unlock(&p->wr_last_meal), true);
		pthread_mutex_unlock(&p->wr_last_meal);
	}
	else
		pthread_mutex_unlock(&p->wr_state);
	return (check);
}

static bool	all_philos_full(t_table *t)
{
	pthread_mutex_lock(&t->wr_full);
	if (t->n_full_philos == t->n_philos)
	{
		pthread_mutex_unlock(&t->wr_full);
		t->all_full = true;
		pthread_mutex_lock(&t->dead_lock);
		t->dead = true;
		pthread_mutex_unlock(&t->dead_lock);
		return (true);
	}
	pthread_mutex_unlock(&t->wr_full);
	return (false);
}

static void	set_end(t_table *t, t_philo *p, bool set_dead_philo)
{
	pthread_mutex_lock(&t->dead_lock);
	t->dead = true;
	pthread_mutex_unlock(&t->dead_lock);
	if (set_dead_philo)
	{
		pthread_mutex_lock(&p->wr_state);
		p->state = DEAD;
		pthread_mutex_unlock(&p->wr_state);
	}
}

int	monitoring(t_table *t)
{
	long long	timestamp;
	int			i;

	while (!t->dead && !all_philos_full(t))
	{
		i = -1;
		while (++i < t->n_philos && !t->dead)
		{
			timestamp = get_timestamp(NULL, NULL);
			if (is_starving(&t->philos[i], timestamp))
			{
				print_state(&t->philos[i], timestamp - t->start_time, true);
				set_end(t, &t->philos[i], true);
			}
			if (all_philos_full(t))
			{
				set_end(t, NULL, false);
				break ;
			}
		}
	}
	return (t->dead + 2 * t->all_full);
}
