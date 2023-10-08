/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdefayes <jdefayes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 22:29:43 by jdefayes          #+#    #+#             */
/*   Updated: 2023/10/08 17:40:01 by jdefayes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philosopher(t_info info)
{
	t_philo		*p;
	pthread_t	main_philo;
	int			i;

	info.philo = malloc(sizeof(t_philo) * (info.nb_of_philo));
	if (info.philo == NULL)
		return (-1);
	init_struct(&info);
	p = info.philo;
	i = 0;
	while (i < info.nb_of_philo)
	{
		if (pthread_create(&p[i].t, NULL, &routine, &(p[i])) != 0)
			return (1);
		i++;
	}
	if (pthread_create(&main_philo, NULL, &check_death, &(info)) != 0)
		return (2);
	waiting_end_of_meal(p);
	destroy_thread_mutex(p, main_philo);
	free(info.philo);
	return (0);
}

void	waiting_end_of_meal(t_philo *p)
{
	int	i;
	int	j;

	if (p->info_p->nb_of_eating != -1)
	{
		while (p->info_p->death == 0)
		{
			j = 0;
			i = 0;
			usleep(600);
			while (i < p->info_p->nb_of_philo)
			{
				if (ft_meals_mtx(0, p, 0, i) >= p->info_p->nb_of_eating) //(p[i].nb_of_meal >= p->info_p->nb_of_eating)
					j++;
				i++;
			}
			if (j >= p->info_p->nb_of_philo)
			{
				ft_death_mtx(1, p->info_p, 1);
			//	p->info_p->death = 1;
				ready_change(1, p->info_p, 2);
			//	p->info_p->ready = 2;
				break ;
			}
		}
	}
}

void	*check_death(void *arg)
{
	int		i;
	t_info	*p;
	long	time;

	p = (t_info *)arg;
	ready_change(1, p, 1);
	//p->ready = 1;
	while (ready_change(0, p, 0) != 2)//(p->ready != 2)
	{
		i = 0;
		usleep(1000);
		while (i < p->nb_of_philo)
		{
			time = get_time(p);
			if (ft_death_time_mtx(0, p->philo, 0, i) <= time)//(p->philo[i].death_time <= time)
			{
				death(p);
				break ;
			}
			i++;
		}
	}
	return (0);
}

void	death(t_info *p)
{
	pthread_mutex_lock(&p->voice);
	printf("%d Philo[%i] \033[31mdied\033[0m\n",
		get_time(p), p->philo->philo_nb);
	ft_death_mtx(1, p, 1);
	//p->death = 1;
	pthread_mutex_unlock(&p->voice);
	ready_change(1, p, 2);
	//p->ready = 2;
}

int	destroy_thread_mutex(t_philo *p, pthread_t main)
{
	int	i;

	i = 0;
	while (i < p->info_p->nb_of_philo)
	{
		if (pthread_join(p[i].t, NULL) != 0)
			return (3);
		i++;
	}
	i = 0;
	while (i < p->info_p->nb_of_philo)
	{
		pthread_mutex_destroy(&p[i].philo_fork);
		i++;
	}
	if (pthread_join(main, NULL) != 0)
		return (4);
	return (0);
}
