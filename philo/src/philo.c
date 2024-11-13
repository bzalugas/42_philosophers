/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 08:20:19 by bazaluga          #+#    #+#             */
/*   Updated: 2024/11/13 08:00:34 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

void	philo_update_state(t_philo *p, t_philo_state new_state)
{
	pthread_mutex_lock(&p->wr_state);
	p->state = new_state;
	pthread_mutex_unlock(&p->wr_state);
}

static void	unlock_forks(t_philo *p, bool fork1, bool fork2)
{
	if (fork1)
		pthread_mutex_unlock(&p->fork1);
	if (fork2)
		pthread_mutex_unlock(p->fork2);
}

int	eat_odd(t_philo *p)
{
	if (check_set_dead(p))
		return (0);
	pthread_mutex_lock(&p->fork1);
	if (check_set_dead(p))
		return (unlock_forks(p, true, false), 0);
	philo_update_state(p, FORKING);
	print_state(p, false);
	if (&p->fork1 == p->fork2)
		return (unlock_forks(p, true, false), 0);
	pthread_mutex_lock(p->fork2);
	if (check_set_dead(p))
		return (unlock_forks(p, true, true), 0);
	print_state(p, false);
	philo_update_state(p, EATING);
	get_timestamp(&p->wr_last_meal, &p->last_meal);
	print_state(p, false);
	p->n_meals++;
	check_set_full(p);
	if (!s_usleep(p->table->eat_time, p))
		return (unlock_forks(p, true, true), 0);
	unlock_forks(p, true, true);
	return (1);
}

int	eat_even(t_philo *p)
{
	if (check_set_dead(p))
		return (0);
	pthread_mutex_lock(p->fork2);
	if (check_set_dead(p))
		return (unlock_forks(p, false, true), 0);
	philo_update_state(p, FORKING);
	print_state(p, false);
	if (&p->fork1 == p->fork2)
		return (unlock_forks(p, false, true), 0);
	pthread_mutex_lock(&p->fork1);
	if (check_set_dead(p))
		return (unlock_forks(p, true, true), 0);
	print_state(p, false);
	philo_update_state(p, EATING);
	get_timestamp(&p->wr_last_meal, &p->last_meal);
	print_state(p, false);
	p->n_meals++;
	check_set_full(p);
	if (!s_usleep(p->table->eat_time, p))
		return (unlock_forks(p, true, true), 0);
	unlock_forks(p, true, true);
	return (1);
}

void	*philo_routine(t_philo *p)
{
	bool	even;

	even = (p->n % 2 == 0);
	while (!check_set_dead(p))
	{
		if (even && !eat_even(p))
			return (NULL);
		else if (!even && !eat_odd(p))
			return (NULL);
		if (check_set_dead(p))
			return (NULL);
		philo_update_state(p, SLEEPING);
		print_state(p, false);
		if (!s_usleep(p->table->slp_time, p))
			return (NULL);
		if (check_set_dead(p))
			return (NULL);
		philo_update_state(p, THINKING);
		print_state(p, false);
		if (p->table->n_philos % 2 != 0
			&& p->table->eat_time >= p->table->slp_time)
			usleep((p->table->eat_time - p->table->slp_time) * 1100);
	}
	return (NULL);
}
