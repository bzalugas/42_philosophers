/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 17:58:24 by bazaluga          #+#    #+#             */
/*   Updated: 2024/11/03 14:44:28 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdlib.h>
# include <string.h>

typedef struct s_philo	t_philo;
typedef struct s_table	t_table;

struct s_table
{
	int		n_philos;
	int		die_time;
	int		eat_time;
	int		slp_time;
	int		max_meals;
	t_philo	*philos;
};

struct s_philo
{
	int	n;

};

/************************************ UTILS ***********************************/
int	ft_putstr_fd(char *s, int fd);
int	ft_atoi(const char *nptr);

/************************************ MAIN ************************************/
// main_utils.c
int	parse_args(t_table *t, char *av[]);
int	init_philos(t_table *t);

#endif
