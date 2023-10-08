/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdefayes <jdefayes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 17:58:20 by jdefayes          #+#    #+#             */
/*   Updated: 2023/10/08 17:58:55 by jdefayes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ready_change(int option, t_info *info, int nb)
{
	int	i;

	if (option == 0)
	{
		pthread_mutex_lock(&info->ready_mtx);
		i = info->ready;
		pthread_mutex_unlock(&info->ready_mtx);
		return (i);
	}
	if (option == 1)
	{
		pthread_mutex_lock(&info->ready_mtx);
		info->ready = nb;
		pthread_mutex_unlock(&info->ready_mtx);
	}
	return (0);
}

int	ft_death_mtx(int option, t_info *info, int nb)
{
	int	i;

	if (option == 0)
	{
		pthread_mutex_lock(&info->death_mtx);
		i = info->death;
		pthread_mutex_unlock(&info->death_mtx);
		return (i);
	}
	if (option == 1)
	{
		pthread_mutex_lock(&info->death_mtx);
		info->death = nb;
		pthread_mutex_unlock(&info->death_mtx);
	}
	return (0);
}

int	ft_death_time_mtx(int option, t_philo *philo, int nb, int philo_nb)
{
	int	i;

	if (option == 0)
	{
		pthread_mutex_lock(&philo->info_p->death_time_mtx);
		i = philo[philo_nb].death_time;
		pthread_mutex_unlock(&philo->info_p->death_time_mtx);
		return (i);
	}
	if (option == 2)
	{
		pthread_mutex_lock(&philo->info_p->death_time_mtx);
		philo->death_time = nb;
		pthread_mutex_unlock(&philo->info_p->death_time_mtx);
	}
	return (0);
}

int	ft_meals_mtx(int option, t_philo *philo, int nb, int philo_nb)
{
	int	i;

	if (option == 0)
	{
		pthread_mutex_lock(&philo->info_p->nb_meal_mtx);
		i = philo[philo_nb].nb_of_meal;
		pthread_mutex_unlock(&philo->info_p->nb_meal_mtx);
		return (i);
	}
	if (option == 2)
	{
		pthread_mutex_lock(&philo->info_p->nb_meal_mtx);
		philo->nb_of_meal = nb;
		pthread_mutex_unlock(&philo->info_p->nb_meal_mtx);
	}
	return (0);
}
