#include "philo.h"

void init_philo(t_info *info)
{
	int i = 0;
	struct timeval start_time;

	gettimeofday(&start_time, NULL);
	//info->start_time = 0;
	info->start_time = (start_time.tv_usec / 1000) + (start_time.tv_sec * 1000);
	//fprintf(stderr, "start time : %ld millisecond \n", info->start_time);
	info->time_to_eat = 500;
	info->time_to_sleep = 300;
	//info->time_to_die = info->time_to_eat + info->time_to_sleep;
	info->time_to_die = 900;
	info->nb_of_eating = 5;
	while(i < info->nb_of_philo)
	{
		//info->philo[i].left_fork = NULL;
		pthread_mutex_init(&info->philo[i].philo_fork, NULL);
		info->philo[i].state = 0;
		info->philo[i].info_p = info;
		info->philo[i].last_meal = 0;
		info->philo[i].philo_nb = i + 1;
		info->philo[i].is_dead = 0;
		info->philo[i].death_time = 0;
		i++;
	}
	i = 0;
	//fprintf(stderr, "check6\n");
	// while(i < info->nb_of_philo)
	// {
	// 	info->philo[i].left_fork = &info->philo[(i + 1) % info->nb_of_philo].philo_fork;
	// 	//fprintf(stderr, "philo[%d].left_fork = info->philo[%d].philo_fork\n", i, ((i +1)% info->nb_of_philo));
	// 	i++;
	// }
	while(i < info->nb_of_philo)
	{
		info->philo[i].s_left_fork.left_fork = &info->philo[(i + 1) % info->nb_of_philo].philo_fork;
		info->philo[i].s_left_fork.taken = 0;
		//fprintf(stderr, "philo[%d] own fork: %p, left fork: %p\n", i, &info->philo[i].philo_fork, info->philo[i].s_left_fork.left_fork);
		i++;
	}
	//fprintf(stderr, "check7\n");
	// i = 0;
	// CONTROLE INFO PHILO
	// while(i < info->nb_of_philo)
	// {
	// 	fprintf(stderr, "philo[%d]>> nb[%d], is_dead: [%d], fork: %p, left_fork: %p\n", i, info->philo[i].philo_nb, info->philo[i].is_dead, &info->philo[i].philo_fork, info->philo[i].left_fork);
	// 	i++;
	// }
}
