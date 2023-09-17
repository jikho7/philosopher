#include "philo.h"

void set_death_time(t_philo *p);
int is_dead (t_philo *p);
int take_fork(t_philo *p);

void* routine(void *arg)
{
	t_philo *p;
	struct timeval current_time;

	gettimeofday(&current_time, NULL);
	p = (t_philo *)arg;
	//fprintf(stderr, "check 7\n");
	// check si philo mort et si fork left dispo
	if (p->philo_nb % 2 == 0)
		usleep(200);
	while(1)
	{
		if (take_fork(p) == 0)
		{
			p->s_left_fork.taken = p->philo_nb;
			pthread_mutex_lock(p->s_left_fork.left_fork);
			break;
		}
	}
	pthread_mutex_lock(&p->philo_fork);

	fprintf(stderr, "%ld ms philo[%d] is waiting for the left fork\n", ((current_time.tv_usec / 1000) + (current_time.tv_sec * 1000) - p->info_p->start_time), p->philo_nb);
	if(p->is_dead == 0)
	{
		//fprintf(stderr, "check 8\n");
		eat(p);
	}
	else
		fprintf(stderr, "philo is \033[31mdead\033[0m\n");
	p->s_left_fork.taken = 0;
	pthread_mutex_unlock(p->s_left_fork.left_fork);
	pthread_mutex_unlock(&p->philo_fork);
	is_sleeping(p);
	is_thinking(p);
	return (0);
}

void eat(t_philo *philo)
{
	long id = (long)philo;
	struct timeval current_time;

	//fprintf(stderr, "check 9\n");
	gettimeofday(&current_time, NULL);
	fprintf(stderr, "%ld ms philo[%i] with id [%li] is ready to eat\n", (current_time.tv_usec / 1000) + (current_time.tv_sec * 1000) - philo->info_p->start_time, philo->philo_nb, id);
	philo->last_meal = (current_time.tv_usec / 1000) + (current_time.tv_sec * 1000) - philo->info_p->start_time;
	//fprintf(stderr, "%ld ms philo[%i] last meal\n", philo->last_meal, philo->philo_nb);

	philo->death_time = philo->last_meal + philo->info_p->time_to_die;
	//philo->death_time = philo->info_p->time_to_die + (current_time.tv_usec / 1000) + (current_time.tv_sec * 1000);
	//fprintf(stderr, "philo[%d] death_time : %d\n", philo->philo_nb, philo->death_time);
	usleep(philo->info_p->time_to_eat * 1000);
}

void is_thinking(t_philo *p)
{
	long id = (long)p;
	struct timeval current_time;

	gettimeofday(&current_time, NULL);
	fprintf(stderr, "%ld philo[%i] with id [%ld] is thinking\n", (current_time.tv_usec / 1000) + (current_time.tv_sec * 1000) - p->info_p->start_time, p->philo_nb, id);
}

void is_sleeping(t_philo *p)
{
	long id = (long)p;
	struct timeval current_time;

	gettimeofday(&current_time, NULL);
	fprintf(stderr, "%ld ms philo[%i] with id [%ld] is ready to sleep for %d\n", (current_time.tv_usec / 1000) + (current_time.tv_sec * 1000) - p->info_p->start_time, p->philo_nb, id, p->info_p->time_to_sleep);
	//while(usleep(p->info_p->time_to_sleep * 1000))
	while(1)
	{
		//fprintf(stderr, "<<check boucle sleeping\n>>");
		if (((current_time.tv_usec / 1000) + (current_time.tv_sec * 1000) - p->info_p->start_time) > p->death_time)
		{
			fprintf(stderr, ">> sleeping control death : philo[%d] should be \033[31mdead\033[0m.\n", p->philo_nb);
			return;
		}
		if (is_dead(p) == 1)
		{
			fprintf(stderr, ">> sleeping control death (is_dead): philo[%d] should be \033[31mdead\033[0m.\n", p->philo_nb);
			return;
		}
	}
}

int is_dead(t_philo *p)
{
	//long id = (long)p;
	struct timeval current_time;

	gettimeofday(&current_time, NULL);
	if ((current_time.tv_usec / 1000) + (current_time.tv_sec * 1000) - p->info_p->start_time > p->death_time)
	{
		p->state = 1;
		fprintf(stderr, "philo[%d] should be \033[31mdead\033[0m.\n", p->philo_nb);
		return (1);
	}
	//fprintf(stderr, "philo[%d] still alive.\n", p->philo_nb);
	return (0);
}

int take_fork(t_philo *p)
{
	if (p->s_left_fork.taken == 0)
	{
		return (0);
	}
	return (p->philo_nb);
}
