/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 17:58:24 by bazaluga          #+#    #+#             */
/*   Updated: 2024/11/08 11:22:29 by bazaluga         ###   ########.fr       */
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
	FORKING,
	EATING,
	THINKING,
	SLEEPING,
	DEAD
}						t_philo_state;

struct s_table
{
	int				n_philos;
	int				die_time;
	int				eat_time;
	int				slp_time;
	int				max_meals;
	long long		start_time;
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
	pthread_mutex_t	fork1;
	pthread_mutex_t	*fork2;
	pthread_mutex_t	wr_last_meal;
	long long		last_meal;
	//add n_meals
	pthread_mutex_t	wr_state;
	t_philo_state	state;
};

/************************************ UTILS ***********************************/
int			ft_putstr_fd(const char *s, int fd);
int			ft_atoi(const char *nptr);
int			write_number(unsigned long long n, bool space);

/************************************ MAIN ************************************/
// main_utils.c
int			init_table(t_table *t);
int			init_philos(t_table *t);
int			parse_args(t_table *t, char *av[]);
int			clean_program(t_table *t, int return_code);
int			stop_error(t_table *t, bool clean, const char *msg);

// monitoring.c
int			monitoring(t_table *t);
long long	get_timestamp(void);

// printing.c
void	ft_swrite(int fd, const void *buf, size_t count, pthread_mutex_t *mutex);
void	print_state(t_philo *p, long long timestamp, bool dead);

// philo.c
/* int		s_usleep(unsigned int usec); */
bool	is_starving(t_philo *p, long long timestamp);
void	*philo_routine(t_philo *p);

#endif
