/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 08:20:19 by bazaluga          #+#    #+#             */
/*   Updated: 2024/11/09 14:44:28 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <unistd.h>

void	philo_update_state(t_philo *p, t_philo_state new_state)
{
	pthread_mutex_lock(&p->wr_state);
	p->state = new_state;
	pthread_mutex_unlock(&p->wr_state);
}

int	eat(t_philo *p)
{
	if (check_set_dead(p))
		return (0);
	pthread_mutex_lock(&p->fork1);
	if (check_set_dead(p))
		return (pthread_mutex_unlock(&p->fork1), 0);
	philo_update_state(p, FORKING);
	print_state(p, get_timestamp(NULL) - p->table->start_time, false);
	pthread_mutex_lock(p->fork2);
	if (check_set_dead(p))
		return (pthread_mutex_unlock(&p->fork1),
			pthread_mutex_unlock(p->fork2), 0);
	print_state(p, get_timestamp(NULL) - p->table->start_time, false);
	philo_update_state(p, EATING);
	print_state(p, get_timestamp(NULL) - p->table->start_time, false);
	if (!s_usleep(p->table->eat_time * 1000, p))
		return (pthread_mutex_unlock(&p->fork1),
			pthread_mutex_unlock(p->fork2), 0);
	p->last_meal = get_timestamp(&p->wr_last_meal);
	p->n_meals++;
	pthread_mutex_unlock(&p->fork1);
	pthread_mutex_unlock(p->fork2);
	if (check_set_full(p))
		return (0);
	return (1);
}

void	*philo_routine(t_philo *p)
{
	while (!check_set_dead(p))
	{
		if (!eat(p))
			return (NULL);
		philo_update_state(p, SLEEPING);
		print_state(p, get_timestamp(NULL) - p->table->start_time, false);
		if (!s_usleep(p->table->slp_time * 1000, p))
			return (NULL);
		philo_update_state(p, THINKING);
		print_state(p, get_timestamp(NULL) - p->table->start_time, false);
	}
	return (NULL);
}
