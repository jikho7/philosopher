#include "philo.h"

void init_philo(t_info *info)
{
	int i = 0;
	struct timeval current_time;

	gettimeofday(&current_time, NULL);
	info->start_time = 0;
	info->start_time = (current_time.tv_usec / 1000) + (current_time.tv_sec * 1000);
	fprintf(stderr, "start time : %ld millisecond \n", info->start_time);
	info->time_to_eat = 5000;
	info->time_to_sleep = 3000;
	info->time_to_die = info->time_to_eat + info->time_to_sleep;
	info->nb_of_eating = 5;
	info->nb = 1;
	//info->time = gettimeofday(&current_time, NULL);

	while(i < info->nb_of_philo)
	{
		pthread_mutex_init(&info->philo[i].right_fork, NULL);
		pthread_mutex_init(&info->philo[i].philo_fork, NULL);
		info->philo[i].state = 0;
		info->philo[i].info_p = info;
		info->philo[i].last_meal = 0;
		info->philo[i].philo_nb = i + 1;
		info->philo[i].is_dead = 0;
		info->philo[i].right_fork = info->philo[i + 1].philo_fork;
		info->philo[i].lifetime = info->time_to_die;
		// info->philo[i].philo_fork = 1;
		// info->philo[i].right_fork = 0;
		i++;
	}
}
