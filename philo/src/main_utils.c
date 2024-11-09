/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 17:41:58 by bazaluga          #+#    #+#             */
/*   Updated: 2024/11/09 14:35:57 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>

int	init_table(t_table *t)
{
	*t = (t_table){0};
	if (pthread_mutex_init(&t->wr_full, NULL))
		return (0);
	if (pthread_mutex_init(&t->fdout, NULL))
		return (0);
	if (pthread_mutex_init(&t->dead_lock, NULL))
		return (0);
	return (1);
}

int	init_philos(t_table *t)
{
	int	i;

	t->philos = malloc(sizeof(t_philo) * t->n_philos);
	if (!t->philos)
		return (ft_putstr_fd("malloc error\n", STDERR_FILENO), 0);
	i = 0;
	while (i < t->n_philos)
	{
		memset(&t->philos[i], 0, sizeof(t_philo));
		t->philos[i].n = i + 1;
		t->philos[i].table = t;
		t->philos[i].n_meals = 0;
		t->philos[i].full = false;
		pthread_mutex_init(&t->philos[i].fork1, NULL);
		pthread_mutex_init(&t->philos[i].wr_state, NULL);
		if (i > 0)
			t->philos[i].fork2 = &t->philos[i - 1].fork1;
		t->philos[i].state = THINKING;
		i++;
	}
	t->philos[0].fork2 = &t->philos[t->n_philos - 1].fork1;
	return (1);
}

int	parse_args(t_table *t, char *av[])
{
	t->n_philos = ft_atoi(av[1]);
	t->die_time = ft_atoi(av[2]);
	t->eat_time = ft_atoi(av[3]);
	t->slp_time = ft_atoi(av[4]);
	t->start_time = 0;
	if (t->n_philos < 1)
		return (stop_error(t, false, "Wrong number of philos\n"));
	if (t->die_time < 1)
		return (stop_error(t, false, "Wrong time_to_die value\n"));
	if (t->eat_time < 1)
		return (stop_error(t, false, "Wrong time_to_eat value\n"));
	if (t->slp_time < 1)
		return (stop_error(t, false, "Wrong time_to_sleep value\n"));
	if (av[5])
	{
		t->max_meals = ft_atoi(av[5]);
		if (t->max_meals < 1)
			return (stop_error(t, false, "Wrong max eat value\n"));
	}
	return (1);
}

int	clean_program(t_table *t, int return_code)
{
	int	i;

	i = -1;
	while (++i < t->n_philos)
	{
		pthread_mutex_unlock(&t->philos[i].fork1);
		pthread_mutex_destroy(&t->philos[i].fork1);
	}
	return (return_code);
}

int	stop_error(t_table *t, bool clean, const char *msg)
{
	write(STDERR_FILENO, "Error: ", 7);
	ft_putstr_fd(msg, STDERR_FILENO);
	if (clean)
		return (clean_program(t, 1));
	return (0);
}
