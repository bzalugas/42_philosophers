/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 09:11:09 by bazaluga          #+#    #+#             */
/*   Updated: 2024/11/07 09:18:36 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_dead(int n_philo, long long timestamp)
{
	write_number(timestamp, true);
	write_number(n_philo, true);
	write(STDOUT_FILENO, "died\n", 5);
}
