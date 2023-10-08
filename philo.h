/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdefayes <jdefayes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 22:29:57 by jdefayes          #+#    #+#             */
/*   Updated: 2023/10/08 17:38:41 by jdefayes         ###   ########.fr       */
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
	long				death_time;
}t_philo;

typedef struct s_info
{
	pthread_mutex_t	voice;
	pthread_mutex_t	ready_mtx;
	pthread_mutex_t	death_mtx;
	pthread_mutex_t	death_time_mtx;
	pthread_mutex_t	nb_meal_mtx;
	pthread_t		main_p;
	int				ready;
	int				death;
	int				nb_of_philo;
	long			start_time;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				nb_of_eating;
	pthread_mutex_t	mutex;
	struct s_philo	*philo;
}t_info;

/*------------- Philosopher -------------*/
int		philosopher(t_info info);
void	waiting_end_of_meal(t_philo *p);
void	*check_death(void *arg);
void	death(t_info *p);
int		destroy_thread_mutex(t_philo *p, pthread_t main);

/*------------- Utils -------------*/
void	wait_philo_and_modulo(t_philo *p);
int		ft_atoi(const char *str);
int		get_time(t_info *p);
void	print_msg(t_philo *p, int msg);

/*------------- Errors -------------*/
int		check_args(char *str);
int		check_nb_of_arg(int ac);

/*------------- Routine -------------*/
void	*routine(void *arg);
void	eat(t_philo *philo);
void	sleep_then_think(t_philo *p);
void	is_sleeping(t_philo *p);
void	is_thinking(t_philo *p);

/*------------- Init -------------*/
void	init_struct(t_info *info);
void	init_philo(t_info *info);
int		ready_change (int option, t_info *info, int nb);
int		ft_death_mtx(int option, t_info *info, int nb);
int		ft_death_time_mtx(int option, t_philo *philo, int nb, int philo_nb);
int		ft_meals_mtx(int option, t_philo *philo, int nb, int philo_nb);

#endif
