/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:50:50 by bazaluga          #+#    #+#             */
/*   Updated: 2024/11/13 10:35:23 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stdbool.h>
#include <sys/time.h>

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

/* static bool	all_philos_full(t_table *t) */
/* { */
/* 	pthread_mutex_lock(&t->wr_full); */
/* 	if (t->n_full_philos == t->n_philos) */
/* 	{ */
/* 		pthread_mutex_unlock(&t->wr_full); */
/* 		pthread_mutex_lock(&t->dead_lock); */
/* 		t->dead = true; */
/* 		pthread_mutex_unlock(&t->dead_lock); */
/* 		return (true); */
/* 	} */
/* 	pthread_mutex_unlock(&t->wr_full); */
/* 	return (false); */
/* } */

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
	bool		dead;

	dead = false;
	while (!dead)
	{
		i = -1;
		while (++i < t->n_philos)
		{
			timestamp = get_timestamp(NULL, NULL);
			pthread_mutex_lock(&t->dead_lock);
			dead = t->dead;
			pthread_mutex_unlock(&t->dead_lock);
			if (is_starving(&t->philos[i], timestamp) || dead)
			{
				set_end(t, &t->philos[i], !dead);
				print_state(&t->philos[i], !dead);
				break ;
			}
		}
	}
	return (0);
}
