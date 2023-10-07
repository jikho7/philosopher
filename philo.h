/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdefayes <jdefayes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 22:29:57 by jdefayes          #+#    #+#             */
/*   Updated: 2023/10/07 15:35:41 by jdefayes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>

typedef struct s_left_fork
{
	int					*neigh_taken;
	int					taken;
	pthread_mutex_t		*left_fork;
}t_left_fork;

/*------------- Strutures -------------*/
typedef struct s_philo
{
	struct s_left_fork	s_left_fork;
	pthread_mutex_t		philo_fork;
	pthread_t			t;
	long				last_meal;
	int					nb_of_meal;
	int					philo_nb;
	struct s_info		*info_p;
//	int					is_dead;
	long				death_time;
}t_philo;

typedef struct s_info
{
	pthread_mutex_t	voice;
	pthread_t		main_p;
	int				ready;
	int				death;
	int				nb_of_philo;
	long			start_time;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				nb_of_eating;
	int				infinite_meal;
	pthread_mutex_t	mutex;
	struct s_philo	*philo;
}t_info;

/*------------- Philosopher -------------*/
int		philosopher(int nb_of_philo, int die, int eat, int sleep,
			int nb_of_meal);
void	generate_philo(t_philo *philo, t_info *info);

/*------------- Utils -------------*/
int		ft_atoi(const char *str);

/*------------- Errors -------------*/
int		check_args(char *str);

/*------------- Routine -------------*/
void	*routine(void *arg);
void	eat(t_philo *philo);
void	is_sleeping(t_philo *p);
void	is_thinking(t_philo *p);

/*------------- Tests -------------*/
void	*print_id(void *arg);
int		ft_is_dead(t_philo *p);
void	print_msg(t_philo *p, int msg);
int		ft_len(char *s);
int		get_time(t_info *p);

void	init_struct(t_info *info, int die, int eat, int sleep);
void	waiting_end_of_meal(t_philo *p);
int		destroy_thread_mutex(t_philo *p, pthread_t main);
void	*check_death(void *arg);
void	wait_philo_and_modulo(t_philo *p);
void	sleep_then_think(t_philo *p);

#endif
