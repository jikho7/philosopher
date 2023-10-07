/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdefayes <jdefayes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 22:29:55 by jdefayes          #+#    #+#             */
/*   Updated: 2023/10/07 17:18:57 by jdefayes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo(t_info *info);

void	init_struct(t_info *info)
{
	struct timeval	start_time;

	gettimeofday(&start_time, NULL);
	pthread_mutex_init(&info->voice, NULL);
	info->start_time = (start_time.tv_usec / 1000) + (start_time.tv_sec * 1000);
	info->ready = 0;
	info->death = 0;
	init_philo(info);
}

void	init_philo(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->nb_of_philo)
	{
		pthread_mutex_init(&info->philo[i].philo_fork, NULL);
		info->philo[i].info_p = info;
		info->philo[i].nb_of_meal = 0;
		info->philo[i].last_meal = 0;
		info->philo[i].philo_nb = i + 1;
		info->philo[i].death_time = info->time_to_die;
		i++;
	}
	i = 0;
	while (i < info->nb_of_philo)
	{
		info->philo[i].s_left_fork.left_fork = &info->philo[(i + 1)
			% info->nb_of_philo].philo_fork;
		i++;
	}
}
