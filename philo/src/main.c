/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 15:57:22 by bazaluga          #+#    #+#             */
/*   Updated: 2024/11/07 13:56:43 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stdio.h>

static void	*philo_routine(void *data)
{
	t_philo	*p;
//do a copy of p->table->start_time
	p = (t_philo *)data;
	pthread_mutex_lock(&p->table->go);
	p->last_meal = p->table->start_time;
	pthread_mutex_unlock(&p->table->go);
	while (1)
	{
		pthread_mutex_lock(&p->table->dead_lock);
		if (p->table->dead)
		{
			pthread_mutex_unlock(&p->table->dead_lock);
			break ;
		}
		pthread_mutex_unlock(&p->table->dead_lock);
	}
	return (NULL);
}

static int	run_philos(t_table *t)
{
	int		i;
	t_philo	*philos;
	int		res;

	philos = t->philos;
	pthread_mutex_lock(&t->go);
	i = -1;
	while (++i < t->n_philos)
		if (pthread_create(&philos[i].tid, NULL, &philo_routine, &philos[i]))
			return (stop_error(t, true, "Error creating philos threads\n"));
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
	return (0);
}
