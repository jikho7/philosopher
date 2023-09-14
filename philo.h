#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#ifndef PHILO_H
#define PHILO_Hq


/*------------- Strutures -------------*/
typedef struct s_philo
{
	int				state;
	pthread_mutex_t	right_fork;
	pthread_mutex_t	philo_fork;
	pthread_t		t;
	int				last_meal;
	int				philo_nb;
	struct s_info	*info_p;
	int				is_dead;
	int				lifetime;
}t_philo;

typedef struct s_info
{
	int				nb_of_philo;
	long			start_time;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_of_eating;
	int				nb;
	pthread_mutex_t	mutex;
	struct s_philo	*philo; // point sur NULL, simple ptr de type struct s_philo != struct philo.
}t_info;



/*------------- Utils -------------*/
void generate_philo(int nb_of_philo, t_philo *philo);
void *own_fork_check(void *arg);
/*------------- Errors -------------*/

/*------------- Routine -------------*/
void *routine(void *arg);
void eat(t_philo *philo);
void* is_eating(void *arg);
void is_sleeping(t_philo *p);
void* is_dying(void *arg);
void is_thinking(t_philo *p);
/*------------- Tests -------------*/
void* test(void *arg);
void* print_id(void *arg);



int ft_len(char *s);
void philosopher(int number_of_philosophers, int time_to_die, int time_to_eat, int time_to_sleep);

#endif

