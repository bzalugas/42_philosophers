/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 08:20:19 by bazaluga          #+#    #+#             */
/*   Updated: 2024/11/08 11:26:47 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <unistd.h>



bool	is_starving(t_philo *p, long long timestamp)
{
	bool	check;

	pthread_mutex_lock(&p->wr_state);
	check = p->state != EATING;
	pthread_mutex_unlock(&p->wr_state);
	pthread_mutex_lock(&p->wr_last_meal);
	check = check && timestamp - p->last_meal >= p->table->die_time;
	pthread_mutex_unlock(&p->wr_last_meal);
	return (check);
}

bool	set_check_dead(t_philo *p)
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
	int				res;

	real_sleep_time = 100;
	i = 0;
	while (i < usec)
	{
		if (i + real_sleep_time > usec)
			real_sleep_time = usec - i;
		res = usleep(real_sleep_time);
		if (res)
			return (res);
		i += real_sleep_time;
		if (set_check_dead(p))
			return (1);
	}
	return (0);
}

void	*philo_routine(t_philo *p)
{
	if (p->table->n_philos <= 1)
		return (NULL);
	while (!set_check_dead(p))
	{
		pthread_mutex_lock(&p->fork1);
		if (set_check_dead(p))
			return (pthread_mutex_unlock(&p->fork1), NULL);
		pthread_mutex_lock(&p->wr_state);
		p->state = FORKING;
		pthread_mutex_unlock(&p->wr_state);
		print_state(p, get_timestamp() - p->table->start_time, false);
		pthread_mutex_lock(p->fork2);
		if (set_check_dead(p))
			return (pthread_mutex_unlock(&p->fork1), pthread_mutex_unlock(p->fork2), NULL);
		print_state(p, get_timestamp() - p->table->start_time, false);
		pthread_mutex_lock(&p->wr_state);
		p->state = EATING;
		pthread_mutex_unlock(&p->wr_state);
		print_state(p, get_timestamp() - p->table->start_time, false);
		s_usleep(p->table->eat_time * 1000, p);
		pthread_mutex_lock(&p->wr_last_meal);
		p->last_meal = get_timestamp();
		pthread_mutex_unlock(&p->wr_last_meal);
		pthread_mutex_unlock(&p->fork1);
		pthread_mutex_unlock(p->fork2);
		if (set_check_dead(p))
			return (NULL);
		pthread_mutex_lock(&p->wr_state);
		p->state = SLEEPING;
		pthread_mutex_unlock(&p->wr_state);
		print_state(p, get_timestamp() - p->table->start_time, false);
		s_usleep(p->table->slp_time * 1000, p);
		pthread_mutex_lock(&p->wr_state);
		if (set_check_dead(p))
			return (pthread_mutex_unlock(&p->wr_state), NULL);
		p->state = THINKING;
		pthread_mutex_unlock(&p->wr_state);
		print_state(p, get_timestamp() - p->table->start_time, false);
	}
	return (NULL);
}
