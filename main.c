#include "philo.h"

void init_philo(t_info *info);
void *check(void *arg);
void *check2(t_philo *p);

int main()
{
	t_info info;
	t_philo *p;
	pthread_t main_philo;
	int i;

	info.nb_of_philo = 5;
	info.philo = malloc(sizeof(t_philo) * (info.nb_of_philo)); // +1 virer, creation des structres.
	init_philo(&info);
	p = info.philo;
	i = 0;
	while (i < info.nb_of_philo)
	{
		//fprintf(stderr, "check\n");
		if (pthread_create(&p[i].t, NULL, &routine, &(p[i])) != 0) // &info.philo[i].t
			return (1);
		i++;
	}
	usleep(100);
	if (pthread_create(&main_philo, NULL, &check, &(info)) != 0)
		return (1);

	i = 0;
	while(1)
	{
		while(p[i].nb_of_meal != p->info_p->nb_of_eating)
			;
		fprintf(stderr, ">>> philo[%i] has eaten enough, i : %d\n", p->philo_nb, i);
		if (i == p->info_p->nb_of_philo)
		{
			fprintf(stderr, "check i: %i\n", i);
			break;
		}
		i++;
	}


	i = 0;
	while(i < info.nb_of_philo)
	{
		if (pthread_join(p[i].t, NULL) != 0)
			return (5);
		i++;
	}
//	fprintf(stderr, "Pthread_join done\n");
	while(i < info.nb_of_philo)
	{
		pthread_mutex_destroy(&info.philo[i].philo_fork);
		i++;
	}
	//fprintf(stderr, "pthread_mutex_destroy done\n");
	if (pthread_join(main_philo, NULL) != 0)
	{
		return (5);
	}
	fprintf(stderr, "Simulation ended\n");
	return 0;
}

void *check(void *arg)
{
	int i = 0;
	t_info *p;
	p = (t_info *)arg;
	struct timeval current_time;
	p->ready = 1;

	gettimeofday(&current_time, NULL);
	while (1)
	{
		//fprintf(stderr, "<<< while(1) >>>\n");
		while (i < p->nb_of_philo)
		{
			//fprintf(stderr, "<<< while(1) inside >>>\n");
			if (p->philo[i].is_dead == 1)
			{
				fprintf(stderr, "%ld Philo[%i] \033[31mdied\033[0m\n", ((current_time.tv_usec / 1000) + (current_time.tv_sec * 1000) - p->start_time), p->philo->philo_nb);
				exit(0);
			}
			i++;
		}
		i = 0;
	}
}

// int main()
// {
// 	t_info info;
// 	t_philo *p;
// 	int i = 0;
// 	// if (atoi(av[1]) == 1)
// 	// {
// 	// 	fprintf(stderr, "Unique philo is dead\n");
// 	// 	return (0);
// 	// }
// 	info.nb_of_philo = 5;
// 	info.philo = malloc(sizeof(t_philo) * (info.nb_of_philo)); // +1 virer, creation des structres.
// 	init_philo(&info);
// 	fprintf(stderr, "check1\n");
// 	p = info.philo;
// 	//pthread_mutex_init(&info.mutex, NULL);
// 	while(info.nb_of_eating > 0)
// 	{
// 		while (i < info.nb_of_philo)
// 		{
// 			if (pthread_create(&p[i].t, NULL, &routine, &(p[i])) != 0) // &info.philo[i].t
// 				return (1);
// 			i++;
// 		}
// 		i = 0;
// 		while(i < info.nb_of_philo)
// 		{
// 			if (pthread_join(p[i].t, NULL) != 0)
// 				return (5);
// 			i++;
// 		}
// 		i = 0;
// 		info.nb_of_eating--;
// 		fprintf(stderr, "nb of eating: %i\n", info.nb_of_eating);
// 	}
// 	i = 0;
// 	while(i < info.nb_of_philo)
// 	{
// 		pthread_mutex_destroy(&info.philo[i].philo_fork);
// 		i++;
// 	}
// 	return 0;
// }
