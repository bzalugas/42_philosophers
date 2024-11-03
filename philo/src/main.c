/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 15:57:22 by bazaluga          #+#    #+#             */
/*   Updated: 2024/11/03 18:09:12 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

void	*philo_routine(void *data)
{
	t_philo	*p;

	p = (t_philo *)data;
	printf("%d\n", p->n);
	return (NULL);
}

int	run_philos(t_table *t)
{
	int		i;
	t_philo	*philos;

	philos = t->philos;
	i = -1;
	while (++i < t->n_philos)
		if (pthread_create(&philos[i].tid, NULL, &philo_routine, &philos[i]))
			break;
	if (i != t->n_philos) //clean all threads already created
		return (ft_putstr_fd("Error when creating threads\n", STDERR_FILENO), 0);
	i = -1;
	while (++i < t->n_philos)
		if (pthread_join(philos[i].tid, NULL))
			break;
	if (i != t->n_philos) //clean all threads already created
		return (ft_putstr_fd("Error when waiting threads\n", STDERR_FILENO), 0);
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
	return (0);
}
