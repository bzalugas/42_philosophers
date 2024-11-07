/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 17:58:24 by bazaluga          #+#    #+#             */
/*   Updated: 2024/11/07 08:54:57 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>

typedef struct s_philo	t_philo;
typedef struct s_table	t_table;

typedef enum e_philo_state
{
	EATING,
	THINKING,
	SLEEPING,
	DEAD
}						t_philo_state;

struct s_table
{
	pthread_t		tid;
	int				n_philos;
	int				die_time;
	int				eat_time;
	int				slp_time;
	int				max_meals;
	pthread_mutex_t	dead_lock;
	bool			dead;
	pthread_mutex_t	fdout;
	t_philo			*philos;
};

struct s_philo
{
	pthread_t		tid;
	int				n;
	t_table			*table;
	pthread_mutex_t	fork;
	pthread_mutex_t	*fork2;
	long long		last_meal;
	pthread_mutex_t	wr_state;
	t_philo_state	state;
};

/************************************ UTILS ***********************************/
int			ft_putstr_fd(const char *s, int fd);
int			ft_atoi(const char *nptr);
int			write_number(unsigned long long n);

/************************************ MAIN ************************************/
// main_utils.c
int			init_philos(t_table *t);
int			parse_args(t_table *t, char *av[]);
int			clean_program(t_table *t, int return_code);
int			stop_error(t_table *t, bool clean, const char *msg);

// monitoring.c
void		*monitoring(void *data);
long long	get_timestamp(void);

#endif
