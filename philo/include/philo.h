/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 17:58:24 by bazaluga          #+#    #+#             */
/*   Updated: 2024/11/12 15:21:32 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdbool.h>

typedef struct s_philo	t_philo;
typedef struct s_table	t_table;

typedef enum e_philo_state
{
	FORKING,
	EATING,
	THINKING,
	SLEEPING,
	DEAD,
}						t_philo_state;

struct s_table
{
	int				n_philos;
	int				die_time;
	int				eat_time;
	int				slp_time;
	int				max_meals;
	pthread_mutex_t	wr_full;
	int				n_full_philos;
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
	int				n_meals;
	pthread_mutex_t	wr_state;
	t_philo_state	state;
	bool			full;
};

/************************************ UTILS ***********************************/
int			ft_putstr_fd(const char *s, int fd);
int			ft_atoi(const char *nptr);
char		*ft_lltoa_cpy(long long n, char *nb);
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
long long	get_timestamp(pthread_mutex_t *mutex, long long *var);

// printing.c
void		print_state(t_philo *p, bool dead);

// philo.c
void		*philo_routine(t_philo *p);

// philo_utils.c
bool		check_end(t_philo *p);
bool		check_set_dead(t_philo *p);
bool		check_set_full(t_philo *p);
int			s_usleep(long long ms, t_philo *p);

#endif
