#include "philo.h"

int philosopher(int nb_of_philo, int t_to_die, int t_to_eat, int t_to_sleep, int nb_of_meal)
{
	t_info info;
	t_philo *p;
	pthread_t main_philo;
	int i;

	info.nb_of_philo = nb_of_philo;
	info.philo = malloc(sizeof(t_philo) * (info.nb_of_philo)); // +1 virer, creation des structres.
	init_struct(&info, t_to_die, t_to_eat, t_to_sleep, nb_of_meal);
	p = info.philo;
	i = 0;
	while (i < info.nb_of_philo)
	{
		if (pthread_create(&p[i].t, NULL, &routine, &(p[i])) != 0) // &info.philo[i].t
			return (1);
		i++;
	}
	if (pthread_create(&main_philo, NULL, &check_death, &(info)) != 0)
		return (2);
	waiting_end_of_meal(p);
	destroy_thread_mutex(p, main_philo);
	free(info.philo);
	return 0;
}

void waiting_end_of_meal(t_philo *p)
{
	int i;

	i = 0;
	while(1)
	{
		while(p[i].nb_of_meal != p->info_p->nb_of_eating)
			;
		if (i == p->info_p->nb_of_philo - 1)
		{
			break;
		}
		i++;
	}
}

void *check_death(void *arg)
{
	int i = 0;
	t_info *p;
	p = (t_info *)arg;
	struct timeval current_time;
	p->ready = 1;

	while (p->ready != 2)
	{
		while (i < p->nb_of_philo)
		{
			if (p->philo[i].is_dead == 1)
			{
				gettimeofday(&current_time, NULL);
				printf("%ld Philo[%i] \033[31mdied\033[0m\n", ((current_time.tv_usec / 1000) + (current_time.tv_sec * 1000) - p->start_time), p->philo->philo_nb);
				exit(0);
			}
			i++;
		}
		i = 0;
	}
	return(0);
}

int destroy_thread_mutex(t_philo *p, pthread_t main)
{
	int i;

	i = 0;
	while(i < p->info_p->nb_of_philo)
	{
		if (pthread_join(p[i].t, NULL) != 0)
			return (3);
		i++;
	}
	i = 0;
	while(i < p->info_p->nb_of_philo)
	{
		pthread_mutex_destroy(&p[i].philo_fork);
		i++;
	}
	p->info_p->ready = 2;
	if (pthread_join(main, NULL) != 0)
		return (4);
	return (0);
}