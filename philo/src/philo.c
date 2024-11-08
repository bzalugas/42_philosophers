/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 08:20:19 by bazaluga          #+#    #+#             */
/*   Updated: 2024/11/08 12:08:08 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <unistd.h>

bool	check_set_dead(t_philo *p)
{
	pthread_mutex_lock(&p->table->dead_lock);
	if (p->table->dead)
	{
		pthread_mutex_unlock(&p->table->dead_lock);
		pthread_mutex_lock(&p->wr_state);
		p->state = DEAD;
		pthread_mutex_unlock(&p->wr_state);
		return (true);
	}
	pthread_mutex_unlock(&p->table->dead_lock);
	return (false);
}

int		s_usleep(unsigned int usec, t_philo *p)
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

int		eat(t_philo *p)
{
	if (check_set_dead(p))
		return (0);
	pthread_mutex_lock(&p->fork1);
	if (check_set_dead(p))
		return (pthread_mutex_unlock(&p->fork1), 0);
	pthread_mutex_lock(&p->wr_state);
	p->state = FORKING;
	pthread_mutex_unlock(&p->wr_state);
	print_state(p, get_timestamp(NULL) - p->table->start_time, false);
	pthread_mutex_lock(p->fork2);
	if (check_set_dead(p))
		return (pthread_mutex_unlock(&p->fork1),
			pthread_mutex_unlock(p->fork2), 0);
	print_state(p, get_timestamp(NULL) - p->table->start_time, false);
	pthread_mutex_lock(&p->wr_state);
	p->state = EATING;
	pthread_mutex_unlock(&p->wr_state);
	print_state(p, get_timestamp(NULL) - p->table->start_time, false);
	if (!s_usleep(p->table->eat_time * 1000, p))
			return (pthread_mutex_unlock(&p->fork1),
			pthread_mutex_unlock(p->fork2), 0);
	p->last_meal = get_timestamp(&p->wr_last_meal);
	pthread_mutex_unlock(&p->fork1);
	pthread_mutex_unlock(p->fork2);
	return (1);
}

void	*philo_routine(t_philo *p)
{
	if (p->table->n_philos <= 1)
		return (NULL);
	while (!check_set_dead(p))
	{
		if (!eat(p))
			return (NULL);
		pthread_mutex_lock(&p->wr_state);
		p->state = SLEEPING;
		pthread_mutex_unlock(&p->wr_state);
		print_state(p, get_timestamp(NULL) - p->table->start_time, false);
		if (!s_usleep(p->table->slp_time * 1000, p))
			return (NULL);
		pthread_mutex_lock(&p->wr_state);
		p->state = THINKING;
		pthread_mutex_unlock(&p->wr_state);
		print_state(p, get_timestamp(NULL) - p->table->start_time, false);
	}
	return (NULL);
}
