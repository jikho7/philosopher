### Fonctions autorisees
memset, printf, malloc, free, write, usleep, gettimeofday, pthread_create, pthread_detach, pthread_join, pthread_mutex_init, pthread_mutex_destroy, pthread_mutex_lock, pthread_mutex_unlock

_sys/time.h_
###### gettimeofday
int gettimeofday ( struct timeval *tp ,  struct timezone *tz )pthread_create
struct    timeval  {
  time_t        tv_sec ;   //used for seconds
  suseconds_t       tv_usec ;   //used for microseconds
  }
 
The 2nd argument points to the **timezone** structure. It should normally be set to NULL because **_struct timezone_** is obsolete.
   


###### pthread_mutex_init
```
int pthread_mutex_init(pthread_mutex_t *mutex,
    const pthread_mutexattr_t *attr);
```
The _pthread_mutex_init()_ function initialises the mutex referenced by _mutex_ with attributes specified by _attr_. If _attr_ is NULL, the default mutex attributes are used; the effect is the same as passing the address of a default mutex attributes object. Upon successful initialisation, the state of the mutex becomes initialised and unlocked.

Attempting to initialise an already initialised mutex results in undefined behaviour.
###### pthread_mutex_destroy
```
int pthread_mutex_init(pthread_mutex_t *mutex,
    const pthread_mutexattr_t *attr);
```
The _pthread_mutex_destroy()_ function destroys the mutex object referenced by _mutex_; the mutex object becomes, in effect, uninitialised. An implementation may cause _pthread_mutex_destroy()_ to set the object referenced by _mutex_ to an invalid value. A destroyed mutex object can be re-initialised using _pthread_mutex_init()_; the results of otherwise referencing the object after it has been destroyed are undefined.

**It is safe to destroy an initialised mutex that is unlocked. Attempting to destroy a locked mutex results in undefined behaviour.**

If successful, the _pthread_mutex_init()_ and _pthread_mutex_destroy()_ functions return zero.

###### pthread_create
int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start)(void *), void *arg); Returns 0 on success, or a positive error number on error

###### pthread_t pthread_self
pthread_t pthread_self(void);
Returns the thread ID of the calling thread

###### pthread_join
int pthread_join(pthread_t thread, void **retval);
Returns 0 on success, or a positive error number on error (comme wait, obtenir l exit statut)

###### pthread_detach
int pthread_detach(pthread_t thread);
Returns 0 on success, or a positive error number on error, quand l exit statut n est pas important, pour nettoyer et supprimer le thread.

###### pthread_mutex_lock
int pthread_mutex_lock(pthread_mutex_t *mutex);

###### pthread_mutex_unlock
int pthread_mutex_unlock(pthread_mutex_t *mutex);
Both return 0 on success, or a positive error number on error

After initialization, a mutex is unlocked.
If more than one other thread is waiting to acquire the mutex unlocked by a call to pthread_mutex_unlock(), it is indeterminate which thread will succeed in acquiring it.

#### Pseudo code

main()
{
    create_main_philo (watch the others, death handling)
    philosopher_ft(param);
}

philo_ft()
{
    while(1)
        is_eating();
        // philo is thinking, waiting;

}

is_eating(t_to_eat, t_to_sleep)
{
    philo.turn = 1; (dans struct commune)

    //philo 1 start

    mutex_block; //savoir si tous les philos attendent patiemment a ce niveau
    if (turn == philo.nb +1) // modulo pour permettre a plusieurs philo de passer
    t_to_die set to 0;
    usleep(t_to_eat);
    usleep(t_to_sleep);
    turn++;
    if (dernier philo)
        reset philo.turn; // turn = 1
    mutex_unblock;
}

