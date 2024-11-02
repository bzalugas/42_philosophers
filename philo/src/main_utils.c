/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 17:41:58 by bazaluga          #+#    #+#             */
/*   Updated: 2024/11/02 17:55:46 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		i++;
	}
	return (1);
}

int	parse_args(t_table *t, char *av[])
{
	*t = (t_table){-1, .philos = NULL};
	t->n_philos = ft_atoi(av[1]);
	t->die_time = ft_atoi(av[2]);
	t->eat_time = ft_atoi(av[3]);
	t->slp_time = ft_atoi(av[4]);
	if (t->n_philos < 1)
		return (ft_putstr_fd("Wrong number of philos\n", STDERR_FILENO), 0);
	if (t->die_time < 1)
		return (ft_putstr_fd("Wrong time_to_die value\n", STDERR_FILENO), 0);
	if (t->eat_time < 1)
		return (ft_putstr_fd("Wrong time_to_eat value\n", STDERR_FILENO), 0);
	if (t->slp_time < 1)
		return (ft_putstr_fd("Wrong time_to_sleep value\n", STDERR_FILENO), 0);
	if (av[5])
	{
		t->max_eat = ft_atoi(av[5]);
		if (t->max_eat < 1)
			return (ft_putstr_fd("Wrong max eat value\n", STDERR_FILENO), 0);
	}
	return (1);
}
