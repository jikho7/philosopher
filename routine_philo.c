#include "philo.h"


void* routine(void *arg)
{
	t_philo *p;

	p = (t_philo *)arg;
	while(p->info_p->ready == 0)
		;
	if (p->philo_nb % 2 == 0)
		usleep(300);
	while((p->nb_of_meal != p->info_p->nb_of_eating) && p->info_p->death == 0)
	{
		pthread_mutex_lock(&p->philo_fork);
		print_msg(p, 0);
		while(1)
		{
			if (ft_is_dead(p) == 1)
			{
				return (0);
			}
			if (p->s_left_fork.taken == 0 && p->info_p->nb_of_philo > 1)
			{
				p->s_left_fork.taken = p->philo_nb;
				pthread_mutex_lock(p->s_left_fork.left_fork);
				printf("%d Philo[%d] has taken the second fork\n", get_time(p->info_p), p->philo_nb);
				break;
			}
		}
		if(p->is_dead == 0)
			eat(p);
		pthread_mutex_unlock(p->s_left_fork.left_fork);
		p->s_left_fork.taken = 0;
		pthread_mutex_unlock(&p->philo_fork);
		if(ft_is_dead(p) == 0)
			is_sleeping(p);
		if(ft_is_dead(p) == 0)
			is_thinking(p);
	}
	return (0);
}


// void lock_mutex(t_philo *p)
// {
// 	struct timeval current_time;

// 	pthread_mutex_lock(&p->philo_fork);
// 	gettimeofday(&current_time, NULL);
// 	fprintf(stderr, "%ld Philo[%d] has taken a fork\n", ((current_time.tv_usec / 1000) + (current_time.tv_sec * 1000) - p->info_p->start_time), p->philo_nb);
// 	while(1)
// 	{
// 		if (p->s_left_fork.taken == 0)
// 		{
// 			p->s_left_fork.taken = p->philo_nb;
// 			pthread_mutex_lock(p->s_left_fork.left_fork);
// 			//fprintf(stderr, "%ld Philo[%d] has taken a second fork\n", ((current_time.tv_usec / 1000) + (current_time.tv_sec * 1000) - p->info_p->start_time), p->philo_nb);
// 			break;
// 		}
// 	}
// 	if(p->is_dead == 0)
// 		eat(p);
// 	pthread_mutex_unlock(p->s_left_fork.left_fork);
// 	p->s_left_fork.taken = 0;
// 	//fprintf(stderr, "%ld ms philo[%d] has released the left fork\n", ((current_time.tv_usec / 1000) + (current_time.tv_sec * 1000) - p->info_p->start_time), p->philo_nb);
// 	pthread_mutex_unlock(&p->philo_fork);
// }

void eat(t_philo *philo)
{
	struct timeval current_time;
	long time1 = 0;
	long time2 = 0;

	gettimeofday(&current_time, NULL);
	print_msg(philo, 1);
	time1 = get_time(philo->info_p);
	philo->last_meal = (current_time.tv_usec / 1000) + (current_time.tv_sec * 1000) - philo->info_p->start_time;
	philo->death_time = philo->last_meal + philo->info_p->time_to_die;
	philo->nb_of_meal = philo->nb_of_meal + 1;
	while(time2 < (time1 + philo->info_p->time_to_eat))
	{
		time2 = get_time(philo->info_p);
		if (ft_is_dead(philo) == 1)
			return;
	}
	// fprintf(stderr, "check time to eat time1: %ld\n", time1);
	// fprintf(stderr, "check time to eat time2: %ld\n", time2);
}

void is_thinking(t_philo *p)
{
	print_msg(p, 2);
}

void is_sleeping(t_philo *p)
{
	struct timeval current_time;
	long time1 = 0;
	long time2 = 0;

	gettimeofday(&current_time, NULL);
	time1 = (current_time.tv_usec / 1000) + (current_time.tv_sec * 1000) - p->info_p->start_time;
	print_msg(p, 3);
	while(time2 < (time1 + p->info_p->time_to_sleep))
	{
		gettimeofday(&current_time, NULL);
		time2 = (current_time.tv_usec / 1000) + (current_time.tv_sec * 1000) - p->info_p->start_time;
		if (ft_is_dead(p) == 1)
			return;
	}
	// fprintf(stderr, "check time to sleep time1: %ld\n", time1);
	// fprintf(stderr, "check time to sleep time2: %ld\n", time2);
}

int ft_is_dead(t_philo *p)
{
	int time = 0;

	time = get_time(p->info_p); //(current_time.tv_usec / 1000) + (current_time.tv_sec * 1000) - p->info_p->start_time;
	if (time > p->death_time)
	{
		p->is_dead = 1;
		p->info_p->death = 1;
		return (1);
	}
	return (0);
}

void print_msg(t_philo *p, int msg)
{
	pthread_mutex_lock(&p->info_p->voice);
	if (p->info_p->death == 0 && msg == 0)
		fprintf(stderr, "%d Philo[%d] has taken a fork\n", get_time(p->info_p), p->philo_nb);
	if (p->info_p->death == 0 && msg == 1)
		printf("%d Philo[%i] \033[33mis eating\033[0m\n", get_time(p->info_p), p->philo_nb);
	if (p->info_p->death == 0 && msg == 2)
		printf("%d Philo[%i] \033[32mis thinking\033[0m\n", get_time(p->info_p), p->philo_nb);
	if (p->info_p->death == 0 && msg == 3)
		printf("%d Philo[%i] \033[34mis sleeping\033[0m\n", get_time(p->info_p), p->philo_nb);	
	pthread_mutex_unlock(&p->info_p->voice);
}