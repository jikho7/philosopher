#include "philo.h"

void init_philo(t_info *info);

int main()
{
	t_info info;
	t_philo *p;
	int i = 0;

	//gettimeofday(&info.start_time, NULL);
	//fprintf(stderr, "start time: %ld\n", (info.start_time.tv_sec * 1000) + (info.start_time.tv_usec / 1000));
	info.nb_of_philo = 5;
	info.philo = malloc(sizeof(t_philo) * (info.nb_of_philo + 1)); // creation des structres.
	init_philo(&info);

	p = info.philo;
	//fprintf(stderr, "check\n");
	pthread_mutex_init(&info.mutex, NULL);
	while(info.nb_of_eating > 0)
	{
		while (i < info.nb_of_philo)
		{
			//if (pthread_create(&p[i].t, NULL, &print_id, &(p[i])) != 0)
			if (pthread_create(&p[i].t, NULL, &routine, &(p[i])) != 0) // &info.philo[i].t
				return (1);
			i++;
		}
		i = 0;
		while(i < info.nb_of_philo)
		{
			if (pthread_join(p[i].t, NULL) != 0)
				return (5);
			i++;
		}
		i = 0;
		info.nb_of_eating--;
		fprintf(stderr, "nb of eating: %i\n", info.nb_of_eating);
	}

	pthread_mutex_destroy(&info.mutex);

	return 0;
}

