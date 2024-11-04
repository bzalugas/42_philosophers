/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:00:54 by bazaluga          #+#    #+#             */
/*   Updated: 2024/11/04 17:15:45 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_state(t_philo *p, long long timestamp)
{
	pthread_mutex_lock(&p->table->fdout);
	(void)timestamp; //=>code write_number
	if (p->state == EATING)
		write(STDOUT_FILENO, "", 1);
	pthread_mutex_unlock(&p->table->fdout);
}
