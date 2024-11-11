/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:00:54 by bazaluga          #+#    #+#             */
/*   Updated: 2024/11/11 16:38:35 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>

void	ft_swrite(int fd, const void *buf, size_t count, pthread_mutex_t *mutex)
{
	pthread_mutex_lock(mutex);
	write(fd, buf, count);
	pthread_mutex_unlock(mutex);
}

void	print_state(t_philo *p, long long timestamp, bool dead)
{
	static char	*txts[5] = {"has taken a fork\n", "is eating\n", "is thinking\n",
		"is sleeping\n", "died\n"};

	if (!dead)
		pthread_mutex_lock(&p->wr_state);
	// pthread_mutex_lock(&p->table->fdout);
	if (check_set_dead(p))
	{
		pthread_mutex_unlock(&p->table->fdout);
		if (!dead)
			pthread_mutex_unlock(&p->wr_state);
		return ;
	}
	write_number(timestamp, true);
	write_number(p->n, true);
	if (dead)
		write(STDOUT_FILENO, "died\n", 5);
	else
		ft_putstr_fd(txts[p->state], STDOUT_FILENO);
	if (!dead)
		pthread_mutex_unlock(&p->wr_state);
	pthread_mutex_unlock(&p->table->fdout);
}
