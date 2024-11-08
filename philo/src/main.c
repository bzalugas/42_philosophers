/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 15:57:22 by bazaluga          #+#    #+#             */
/*   Updated: 2024/11/08 09:32:18 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stdio.h>

static int	run_philos(t_table *t)
{
	int		i;
	t_philo	*philos;
	int		res;

	philos = t->philos;
	t->start_time = get_timestamp();
	i = -1;
	while (++i < t->n_philos)
	{
		philos[i].last_meal = t->start_time;
		if (pthread_create(&philos[i].tid, NULL, (void *)(void *)philo_routine,
			&philos[i]))
			return (stop_error(t, true, "Error creating philos threads\n"));
	}
	res = monitoring(t);
	i = -1;
	while (++i < t->n_philos)
		if (pthread_join(philos[i].tid, NULL))
			return (stop_error(t, true, "Error waiting philos threads\n"));
	return (res);
}
//For sleep do a smart_sleep that keeps checking if someone is dead
int	main(int ac, char *av[])
{
	t_table	table;

	if (ac < 5 || ac > 6)
		return (stop_error(&table, false, "Wrong argument number: ./philo \
n_philos time_to_die time_to_eat time_to_sleep [max_eating_number]\n"));
	if (!init_table(&table))
		return (1);
	if (!parse_args(&table, av))
		return (1);
	if (!init_philos(&table))
		return (1);
	if (!run_philos(&table))
		return (1);
	return (0);
}
