/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 12:39:32 by bazaluga          #+#    #+#             */
/*   Updated: 2024/11/09 13:28:27 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_set_dead(t_philo *p)
{
	pthread_mutex_lock(&p->table->dead_lock);
	if (p->table->dead)
	{
		pthread_mutex_unlock(&p->table->dead_lock);
		/* pthread_mutex_lock(&p->wr_state); */
		/* p->state = DEAD; */
		/* pthread_mutex_unlock(&p->wr_state); */
		return (true);
	}
	pthread_mutex_unlock(&p->table->dead_lock);
	return (false);
}

bool	check_set_full(t_philo *p)
{
	if (p->full)
		return (true);
	if (p->n_meals >= p->table->max_meals)
	{
		p->full = true;
		pthread_mutex_lock(&p->table->wr_full);
		p->table->n_full_philos++;
		pthread_mutex_unlock(&p->table->wr_full);
		return (true);
	}
	return (false);
}

int	s_usleep(unsigned int usec, t_philo *p)
{
	unsigned int	real_sleep_time;
	unsigned int	i;

	real_sleep_time = 100;
	i = 0;
	while (i < usec)
	{
		if (i + real_sleep_time > usec)
			real_sleep_time = usec - i;
		if (usleep(real_sleep_time))
			return (0);
		i += real_sleep_time;
		if (check_set_dead(p))
			return (0);
	}
	return (1);
}