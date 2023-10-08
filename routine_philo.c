/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdefayes <jdefayes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 22:29:48 by jdefayes          #+#    #+#             */
/*   Updated: 2023/10/08 17:49:58 by jdefayes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	wait_philo_and_modulo(p);
	while (ft_death_mtx(0, p->info_p, 0) == 0)//(p->info_p->death == 0)
	{
		pthread_mutex_lock(&p->philo_fork);
		print_msg(p, 0);
		while (p->info_p->nb_of_philo == 1)
		{
			if (ft_death_mtx(0, p->info_p, 0))//(p->info_p->death == 1)
			{
				pthread_mutex_unlock(&p->philo_fork);
				return (0);
			}
		}
		pthread_mutex_lock(p->s_left_fork.left_fork);
		print_msg(p, 4);
		eat(p);
		pthread_mutex_unlock(p->s_left_fork.left_fork);
		pthread_mutex_unlock(&p->philo_fork);
		sleep_then_think(p);
	}
	return (0);
}

void	eat(t_philo *philo)
{
	long	time1;
	long	time2;

	time2 = 0;
	print_msg(philo, 1);
	time1 = get_time(philo->info_p);
	philo->last_meal = get_time(philo->info_p);
	ft_death_time_mtx(2, philo, (philo->last_meal + philo->info_p->time_to_die), 0);
//	philo->death_time = philo->last_meal + philo->info_p->time_to_die;
	ft_meals_mtx(2, philo, (philo->nb_of_meal + 1), 0);
//	philo->nb_of_meal = philo->nb_of_meal + 1;
	while (time2 < (time1 + philo->info_p->time_to_eat))
	{
		usleep(700);
		time2 = get_time(philo->info_p);
	}
}

void	is_thinking(t_philo *p)
{
	print_msg(p, 2);
}

void	is_sleeping(t_philo *p)
{
	long	time1;
	long	time2;

	time2 = 0;
	time1 = get_time(p->info_p);
	print_msg(p, 3);
	while (time2 < (time1 + p->info_p->time_to_sleep))
	{
		usleep(700);
		time2 = get_time(p->info_p);
	}
}

void	sleep_then_think(t_philo *p)
{
	is_sleeping(p);
	is_thinking(p);
}


int ready_change(int option, t_info *info, int nb)
{
	int i;

	if (option == 0)// read
	{
		pthread_mutex_lock(&info->ready_mtx);
		i = info->ready;
		pthread_mutex_unlock(&info->ready_mtx);
		return (i);
	}
	if (option == 1)// change
	{
		pthread_mutex_lock(&info->ready_mtx);
		info->ready = nb;
		pthread_mutex_unlock(&info->ready_mtx);
	}
	return (0);
}

int ft_death_mtx(int option, t_info *info, int nb)
{
	int i;

	if (option == 0)// read
	{
		pthread_mutex_lock(&info->death_mtx);
		i = info->death;
		pthread_mutex_unlock(&info->death_mtx);
		return (i);
	}
	if (option == 1)// change
	{
		pthread_mutex_lock(&info->death_mtx);
		info->death = nb;
		pthread_mutex_unlock(&info->death_mtx);
	}
	return (0);
}

int ft_death_time_mtx(int option, t_philo *philo, int nb, int philo_nb)
{
	int i;

	if (option == 0)// read
	{
		pthread_mutex_lock(&philo->info_p->death_time_mtx);
		i = philo[philo_nb].death_time;
		pthread_mutex_unlock(&philo->info_p->death_time_mtx);
		return (i);
	}
	if (option == 2)// change
	{
		pthread_mutex_lock(&philo->info_p->death_time_mtx);
		philo->death_time = nb;
		pthread_mutex_unlock(&philo->info_p->death_time_mtx);
	}
	return (0);
}

int ft_meals_mtx(int option, t_philo *philo, int nb, int philo_nb)
{
	int i;

	if (option == 0)// read
	{
		pthread_mutex_lock(&philo->info_p->nb_meal_mtx);
		i = philo[philo_nb].nb_of_meal;
		pthread_mutex_unlock(&philo->info_p->nb_meal_mtx);
		return (i);
	}
	if (option == 2)// change
	{
		pthread_mutex_lock(&philo->info_p->nb_meal_mtx);
		philo->nb_of_meal = nb;
		pthread_mutex_unlock(&philo->info_p->nb_meal_mtx);
	}
	return (0);
}
