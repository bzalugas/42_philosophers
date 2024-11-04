/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 15:57:22 by bazaluga          #+#    #+#             */
/*   Updated: 2024/11/04 17:16:17 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stdio.h>

static void	*philo_routine(void *data)
{
	t_philo	*p;

	p = (t_philo *)data;
	p->last_meal = get_timestamp();
	while (1)
	{
		pthread_mutex_lock(&p->table->dead_lock);
		if (!p->table->dead)
			break ;
		pthread_mutex_unlock(&p->table->dead_lock);
	}
	return (NULL);
}

static int	run_philos(t_table *t)
{
	int		i;
	t_philo	*philos;

	philos = t->philos;
	i = -1;
	while (++i < t->n_philos)
		if (pthread_create(&philos[i].tid, NULL, &philo_routine, &philos[i]))
			return (stop_error(t, true, "Error when creating threads\n"));
	i = -1;
	while (++i < t->n_philos)
		if (pthread_join(philos[i].tid, NULL))
			return (stop_error(t, true, "Error when waiting threads\n"));
	return (1);
}

int	main(int ac, char *av[])
{
	t_table	table;

	if (ac < 5 || ac > 6)
	{
		ft_putstr_fd("Wrong argument number: ./philo n_philos time_to_die \
time_to_eat time_to_sleep [max_eating_number]\n", STDERR_FILENO);
		return (1);
	}
	if (!parse_args(&table, av))
		return (1);
	if (!init_philos(&table))
		return (1);
	if (!run_philos(&table))
		return (1);
	write_number(0);
	return (0);
}
