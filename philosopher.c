/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdefayes <jdefayes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 22:29:43 by jdefayes          #+#    #+#             */
/*   Updated: 2023/10/07 15:35:46 by jdefayes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philosopher(int philos, int die, int eat, int sleep, int meals)
{
	t_info		info;
	t_philo		*p;
	pthread_t	main_philo;
	int			i;

	info.nb_of_philo = philos;
	// verif si meals ou pas
	info.nb_of_eating = meals;
	info.philo = malloc(sizeof(t_philo) * (info.nb_of_philo));
	if (info.philo == NULL)
		return (-1);
	init_struct(&info, die, eat, sleep);
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

	i = 0;
	while (p->info_p->death == 0)// faire mieux(1)
	{
		usleep(600);
		if (p[i].nb_of_meal == p->info_p->nb_of_eating)// !infinite &&
			i++;
		if (i == p->info_p->nb_of_philo - 1)
		{
			break ;
		}
	}
}

void	*check_death(void *arg)
{
	int		i;
	t_info	*p;
	long time;

	p = (t_info *)arg;
	p->ready = 1;
	while (p->ready != 2)
	{
		i = 0;
		usleep(1000);
		while (i < p->nb_of_philo)
		{
			time = get_time(p);
			if (p->philo[i].death_time <= time)
			{
				pthread_mutex_lock(&p->voice);
				printf("%d Philo[%i] \033[31mdied 5\033[0m\n",
						get_time(p), p->philo->philo_nb);
				p->death = 1;
				pthread_mutex_unlock(&p->voice);
				p->ready = 2;
				break;
			}
			i++;
		}
	}
	return (0);
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
	p->info_p->ready = 2;
	if (pthread_join(main, NULL) != 0)
		return (4);
	return (0);
}
