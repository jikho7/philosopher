#include "philo.h"

void* routine(void *arg)
{
	t_philo *p;

	p = (t_philo *)arg;
	pthread_mutex_lock(&p->philo_fork);
	//fprintf(stderr, "philo[%d] is waiting for the right fork\n", p->philo_nb);
	pthread_mutex_lock(&p->right_fork);
	if(p->is_dead == 0)
	{
		//eat(p);
	}
	else
		fprintf(stderr, "philo is dead\n");
	pthread_mutex_unlock(&p->right_fork);
	pthread_mutex_unlock(&p->philo_fork);
	//is_sleeping(p);
	//is_thinking(p);
	return (0);
}

// void *own_fork_check(void *arg)
// {

// }

void eat(t_philo *philo)
{
	//long id = (long)philo;
	t_philo *s;

	s = (t_philo *)philo;
	//fprintf(stderr, "philo[%i] with id [%li] is ready to eat\n", philo->philo_nb, id);
	philo->lifetime = philo->info_p->time_to_die;
	usleep(philo->info_p->time_to_eat);
}

// void* is_eating(void *arg)
// {
// 	printf("eat\n");
// }

void is_thinking(t_philo *p)
{
	long id = (long)p;
	fprintf(stderr, "philo[%i] with id [%ld] is thinking\n", p->philo_nb, id);
}

void is_sleeping(t_philo *p)
{
	//long id = (long)p;

	//fprintf(stderr, "philo[%i] with id [%ld] is ready to sleep for %d\n", p->philo_nb, id, p->info_p->time_to_sleep);
	usleep(p->info_p->time_to_sleep);
}
