/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdefayes <jdefayes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 22:29:48 by jdefayes          #+#    #+#             */
/*   Updated: 2023/10/07 12:14:33 by jdefayes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	wait_philo_and_modulo(p);
	while (p->nb_of_meal != p->info_p->nb_of_eating)
	{
		pthread_mutex_lock(&p->philo_fork);
		print_msg(p, 0);
		if (p->info_p->nb_of_philo > 1)
		{
			pthread_mutex_lock(p->s_left_fork.left_fork);
			print_msg(p, 4);
		}
		eat(p);
		pthread_mutex_unlock(p->s_left_fork.left_fork);
		pthread_mutex_unlock(&p->philo_fork);
		sleep_then_think(p);
	}
	return (0);
}

void	eat(t_philo *philo)
{
	struct timeval	current_time;
	long			time1;
	long			time2;

	time1 = 0;
	time2 = 0;
	gettimeofday(&current_time, NULL);
	print_msg(philo, 1);
	time1 = get_time(philo->info_p);
	philo->last_meal = (current_time.tv_usec / 1000)
		+ (current_time.tv_sec * 1000) - philo->info_p->start_time;
	philo->death_time = philo->last_meal + philo->info_p->time_to_die;
	philo->nb_of_meal = philo->nb_of_meal + 1;
	while (time2 < (time1 + philo->info_p->time_to_eat))
	{
		time2 = get_time(philo->info_p);
	}
}

void	is_thinking(t_philo *p)
{
	print_msg(p, 2);
}

void	is_sleeping(t_philo *p)
{
	struct timeval	current_time;
	long			time1;
	long			time2;

	time1 = 0;
	time2 = 0;
	gettimeofday(&current_time, NULL);
	time1 = (current_time.tv_usec / 1000)
		+ (current_time.tv_sec * 1000) - p->info_p->start_time;
	print_msg(p, 3);
	while (time2 < (time1 + p->info_p->time_to_sleep))
	{
		time2 = get_time(p->info_p);
	}
}

void	sleep_then_think(t_philo *p)
{
	is_sleeping(p);
	is_thinking(p);
}
