#include "philo.h"

void set_death_time(t_philo *p);
int ft_is_dead (t_philo *p);
int take_fork(t_philo *p);

// timestamp_in_ms X has taken a fork
// ◦ timestamp_in_ms X is eating
// ◦ timestamp_in_ms X is sleeping
// ◦ timestamp_in_ms X is thinking
// ◦ timestamp_in_ms X died

void* routine(void *arg)
{
	t_philo *p;
	struct timeval current_time;

	gettimeofday(&current_time, NULL);
	p = (t_philo *)arg;
	//fprintf(stderr, "check 77\n");
	// check si philo mort et si fork left dispo
	//fprintf(stderr, "is ready: %d\n", p->info_p->ready);
	while(p->info_p->ready == 0)
	{
		;
	}
	//fprintf(stderr, "END boucle ready\n");
	if (p->philo_nb % 2 == 0)
		usleep(100);


	while((p->nb_of_meal != p->info_p->nb_of_eating))
	{
		pthread_mutex_lock(&p->philo_fork);
		fprintf(stderr, "%ld Philo[%d] has taken a fork\n", ((current_time.tv_usec / 1000) + (current_time.tv_sec * 1000) - p->info_p->start_time), p->philo_nb);
		while(1)
		{
			if (p->s_left_fork.taken == 0)
			{
				p->s_left_fork.taken = p->philo_nb;
				pthread_mutex_lock(p->s_left_fork.left_fork);
				fprintf(stderr, "%ld Philo[%d] has taken a second fork\n", ((current_time.tv_usec / 1000) + (current_time.tv_sec * 1000) - p->info_p->start_time), p->philo_nb);
				break;
			}
		}
		if(p->is_dead == 0)
		{
			eat(p);
		}
		else
			fprintf(stderr, "philo is \033[31mdead\033[0m\n");
		pthread_mutex_unlock(p->s_left_fork.left_fork);
		p->s_left_fork.taken = 0;
		fprintf(stderr, "%ld ms philo[%d] has released the left fork\n", ((current_time.tv_usec / 1000) + (current_time.tv_sec * 1000) - p->info_p->start_time), p->philo_nb);
		pthread_mutex_unlock(&p->philo_fork);
		is_sleeping(p);
		is_thinking(p);
	}
	return (0);
}

void eat(t_philo *philo)
{
	//long id = (long)philo;
	struct timeval current_time;

	gettimeofday(&current_time, NULL);
	fprintf(stderr, "%ld Philo[%i] \033[33mis eating\033[0m\n", (current_time.tv_usec / 1000) + (current_time.tv_sec * 1000) - philo->info_p->start_time, philo->philo_nb);
	philo->last_meal = (current_time.tv_usec / 1000) + (current_time.tv_sec * 1000) - philo->info_p->start_time;
	//fprintf(stderr, "%ld ms philo[%i] last meal\n", philo->last_meal, philo->philo_nb);

	philo->death_time = philo->last_meal + philo->info_p->time_to_die;
	philo->nb_of_meal = philo->nb_of_meal + 1;
	fprintf(stderr, "philo[%i] number of meal: %d\n", philo->philo_nb, philo->nb_of_meal);
	//philo->death_time = philo->info_p->time_to_die + (current_time.tv_usec / 1000) + (current_time.tv_sec * 1000);
	//fprintf(stderr, "philo[%d] death_time : %ld\n", philo->philo_nb, philo->death_time);
	usleep(philo->info_p->time_to_eat * 1000);
}

void is_thinking(t_philo *p)
{
	//long id = (long)p;
	struct timeval current_time;

	gettimeofday(&current_time, NULL);
	fprintf(stderr, "%ld Philo[%i] \033[32mis thinking\033[0m\n", (current_time.tv_usec / 1000) + (current_time.tv_sec * 1000) - p->info_p->start_time, p->philo_nb);
}

void is_sleeping(t_philo *p)
{
	//long id = (long)p;
	struct timeval current_time;
	long time1 = 0;
	long time2 = 0;

	gettimeofday(&current_time, NULL);
	time1 = (current_time.tv_usec / 1000) + (current_time.tv_sec * 1000) - p->info_p->start_time;
	fprintf(stderr, "%ld Philo[%i] \033[34mis sleeping\033[0m\n", (current_time.tv_usec / 1000) + (current_time.tv_sec * 1000) - p->info_p->start_time, p->philo_nb);
	//while(usleep(p->info_p->time_to_sleep * 1000))
	while(time2 < (time1 + p->info_p->time_to_sleep))
	{
		gettimeofday(&current_time, NULL);
		time2 = (current_time.tv_usec / 1000) + (current_time.tv_sec * 1000) - p->info_p->start_time;
		//fprintf(stderr, "<<check boucle sleeping\n>>");
		if (((current_time.tv_usec / 1000) + (current_time.tv_sec * 1000) - p->info_p->start_time) > p->death_time)
		{
			fprintf(stderr, ">> sleeping control death : philo[%d] should be \033[31mdead\033[0m.\n", p->philo_nb);
			return;
		}
		if (ft_is_dead(p) == 1)
		{
			fprintf(stderr, ">> sleeping control death (is_dead): philo[%d] should be \033[31mdead\033[0m.\n", p->philo_nb);
			return;
		}
	}
}

int ft_is_dead(t_philo *p)
{
	//long id = (long)p;
	struct timeval current_time;
	long time = 0;

	gettimeofday(&current_time, NULL);
	time = (current_time.tv_usec / 1000) + (current_time.tv_sec * 1000) - p->info_p->start_time;
	if (time > p->death_time)
	{
		p->state = 1;
		fprintf(stderr, "%ld Philo[%d] should be \033[31mdead\033[0m.\n", (current_time.tv_usec / 1000) + (current_time.tv_sec * 1000) - p->info_p->start_time, p->philo_nb);
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
