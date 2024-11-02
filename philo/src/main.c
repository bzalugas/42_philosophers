/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 15:57:22 by bazaluga          #+#    #+#             */
/*   Updated: 2024/11/02 17:57:06 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

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
	int i = -1;
	while (++i < table.n_philos)
		printf("philo %d: \n", table.philos[i].n);
	return (0);
}
