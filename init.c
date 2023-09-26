#include "philo.h"

//void init_philo(t_info *info);

void init_struct(t_info *info, int die, int eat, int sleep, int meals)
{
	int i = 0;
	struct timeval start_time;

	gettimeofday(&start_time, NULL);
	info->start_time = (start_time.tv_usec / 1000) + (start_time.tv_sec * 1000);
	info->time_to_die = die;
	info->time_to_eat = eat;
	info->time_to_sleep = sleep;
	info->nb_of_eating = meals;
	info->ready = 0;
	info->death = 0;
	//fprintf(stderr, "nb of MEAL: %d\n", info->nb_of_eating);
	//init_philo(info);
	while(i < info->nb_of_philo)
	{
		pthread_mutex_init(&info->philo[i].philo_fork, NULL);
		info->philo[i].info_p = info;
		info->philo[i].nb_of_meal = 0;
		info->philo[i].last_meal = 0;
		info->philo[i].philo_nb = i + 1;
		info->philo[i].is_dead = 0;
		info->philo[i].death_time = die;
		i++;
	}
	i = 0;
	while(i < info->nb_of_philo)
	{
		info->philo[i].s_left_fork.left_fork = &info->philo[(i + 1) % info->nb_of_philo].philo_fork;
		info->philo[i].s_left_fork.taken = 0;
		info->philo[i].s_left_fork.neigh_taken = &info->philo[(i + 1) % info->nb_of_philo].s_left_fork.taken;
		i++;
	}
//  	i = 0;
// // 	//CONTROLE INFO PHILO
// 	while(i < info->nb_of_philo)
// 	{
// 		//fprintf(stderr, "philo[%d]>> nb[%d], is_dead: [%d], fork: %p, left_fork: %p\n", i, info->philo[i].philo_nb, info->philo[i].is_dead, &info->philo[i].philo_fork, info->philo[i].s_left_fork.left_fork);
// 		fprintf(stderr, "adresse philo[%i]neigh_taken: %p\n adresse philo[%i]taken: %p\n value : %d \n", i, info->philo[i].s_left_fork.neigh_taken, i, &info->philo[i].s_left_fork.taken, *info->philo[i].s_left_fork.neigh_taken);
// 		i++;
// 	}
}

// void init_philo(t_info *info)
// {
// 	int i;

// 	i = 0;
// 	while(i < info->nb_of_philo)
// 	{
// 		pthread_mutex_init(&info->philo[i].philo_fork, NULL);
// 		info->philo[i].info_p = info;
// 		info->philo[i].nb_of_meal = 0;
// 		info->philo[i].last_meal = 0;
// 		info->philo[i].philo_nb = i + 1;
// 		info->philo[i].is_dead = 0;
// 		info->philo[i].death_time = 0;
// 		i++;
// 	}
// 	i = 0;
// 	while(i < info->nb_of_philo)
// 	{
// 		info->philo[i].s_left_fork.left_fork = &info->philo[(i + 1) % info->nb_of_philo].philo_fork;
// 		info->philo[i].s_left_fork.taken = 0;
// 		info->philo[i].s_left_fork.neigh_taken = &info->philo[(i + 1) % info->nb_of_philo].s_left_fork.taken;
// 		i++;
// 	}
// }