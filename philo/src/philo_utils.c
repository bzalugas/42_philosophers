/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 12:39:32 by bazaluga          #+#    #+#             */
/*   Updated: 2024/11/13 09:29:17 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

bool	check_set_dead(t_philo *p)
{
	pthread_mutex_lock(&p->table->dead_lock);
	if (p->table->dead)
	{
		pthread_mutex_unlock(&p->table->dead_lock);
		return (true);
	}
	pthread_mutex_unlock(&p->table->dead_lock);
	return (false);
}

bool	check_set_full(t_philo *p)
{
	if (p->full)
		return (true);
	pthread_mutex_lock(&p->table->dead_lock);
	if (p->table->max_meals > 0 && p->n_meals >= p->table->max_meals)
	{
		p->full = true;
		pthread_mutex_lock(&p->table->wr_full);
		p->table->n_full_philos++;
		if (p->table->n_full_philos == p->table->n_philos)
			p->table->dead = true;
		pthread_mutex_unlock(&p->table->wr_full);
		pthread_mutex_unlock(&p->table->dead_lock);
		return (true);
	}
	pthread_mutex_unlock(&p->table->dead_lock);
	return (false);
}

int	s_usleep(long long ms, t_philo *p)
{
	long long	start;
	long long	end;

	start = get_timestamp(NULL, NULL);
	end = start + ms;
	while (1)
	{
		if (get_timestamp(NULL, NULL) >= end)
			return (1);
		if (check_set_dead(p))
			return (0);
		if (usleep(100))
			return (0);
		if (get_timestamp(NULL, NULL) >= end)
			return (1);
		if (check_set_dead(p))
			return (0);
		if (usleep(100))
			return (0);
	}
	return (1);
}
