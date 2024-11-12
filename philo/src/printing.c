/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:00:54 by bazaluga          #+#    #+#             */
/*   Updated: 2024/11/12 11:26:41 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_swrite(int fd, const void *buf, size_t count, pthread_mutex_t *mutex)
{
	pthread_mutex_lock(mutex);
	write(fd, buf, count);
	pthread_mutex_unlock(mutex);
}

static void	create_str(t_philo *p, long long timestamp, char *str, bool dead)
{
	static char		*txts[5] = {"has taken a fork\n", "is eating\n",
		"is thinking\n", "is sleeping\n", "died\n"};
	char			*ptr;
	int				i;
	t_philo_state	state;

	ptr = ft_lltoa_cpy(timestamp, str);
	*(ptr++) = ' ';
	ptr = ft_lltoa_cpy(p->n, ptr);
	*(ptr++) = ' ';
	if (dead)
		state = DEAD;
	else
	{
		pthread_mutex_lock(&p->wr_state);
		state = p->state;
		pthread_mutex_unlock(&p->wr_state);
	}
	i = -1;
	while (txts[state][++i])
		ptr[i] = txts[state][i];
	ptr[i] = 0;
}

void	print_state(t_philo *p, long long timestamp, bool dead)
{
	char	str[50];

	pthread_mutex_lock(&p->table->fdout);
	timestamp = get_timestamp(NULL, NULL) - p->table->start_time;
	create_str(p, timestamp, str, dead);
	if (check_set_dead(p))
	{
		pthread_mutex_unlock(&p->table->fdout);
		return ;
	}
	/* write_number(timestamp, true); */
	/* write_number(p->n, true); */
	/* if (dead) */
		/* write(STDOUT_FILENO, "died\n", 5); */
	/* else */
		/* ft_putstr_fd(txts[p->state], STDOUT_FILENO); */
	ft_putstr_fd(str, STDOUT_FILENO);
	pthread_mutex_unlock(&p->table->fdout);
}
