#include "philo.h"

// void* print_id(void *arg)
// {
// 	long id = (long)arg;
// 	t_philo *s;
// 	int i = 0;

// 	s = (t_philo *)arg;
// 	fprintf(stderr, "philo [%i] id: %ld\n", i, id);
// 	return (0);
// }

// void* test(void *arg) // traite struct philo
// {
// 	t_philo *s;
// 	int j;

// 	s = (t_philo *)arg;
// 	pthread_mutex_lock(&s->info_p->mutex);
// 	j = 10;
// 	//fprintf(stderr, "enter to lockzone \n");
// 	while(j > 0)
// 	{
// 		print_id(arg);
// 		//fprintf(stderr, "nb : %d, j: %d\n", s->info_p->nb, j);
// 		j--;
// 		s->info_p->nb++;
// 	}
// 	pthread_mutex_unlock(&s->info_p->mutex);
// 	//printf("x = %d\n", s->info_p->nb);
// 	return(0);
// }

