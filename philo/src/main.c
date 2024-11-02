/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 15:57:22 by bazaluga          #+#    #+#             */
/*   Updated: 2024/11/02 16:42:45 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char *av[])
{
	(void)av;
	if (ac < 4 || ac > 5)
	{
		ft_putstr_fd("Wrong argument number: ./philo n_philos time_to_die \
time_to_eat time_to_sleep [max_eating_number]\n", STDERR_FILENO);
		return (1);
	}
}
