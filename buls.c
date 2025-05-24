#include "philo.h"

int	ft_atoi(const char *str)
{
	int	op;
	int	final;

	op = 1;
	final = 0;
	while ((*str == 32) || (*str >= 9 && *str <= 13))
	{
		str++;
	}
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			op *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		final = (final * 10) + (*str - '0');
		str++;
	}
	return (final * op);
}

//           ms   ms  ms
// ./philo 5 800 200 200
void check_inputs(t_info *info, char **av)
{
	info->nmb_philo = atoi(av[1]); // atoi make it long
	info->time_die = atoi(av[2]); // atoi(av[2]) * 1000 or 1e3 (to convert the milisecond to microsend )
	info->time_sleep = atoi(av[3]);
	info->time_eat = atoi(av[4]);
	info->limit_meals = -1;
	if (av[5])
		info->limit_meals = atoi(av[5]);
}

// right fork = philo_id - 1 (philo position in the array) = 4
// left fork = [philo_position + 1] % philo_nmb = [4 + 1] % 5 = 0
void init_forks(t_philo *philo, t_fork *forks, int philo_pos)
{
	int philo_nb;

	philo_nb = philo->infos->nmb_philo;
	// deadlock problem here
	if (philo->id % 2 == 0)
	{
		philo->right = &forks[philo_pos];
		philo->left = &forks[(philo_pos + 1) % philo_nb];
	}
	else else
	{
		philo->right = &forks[(philo_pos + 1) % philo_nb];
		philo->left = &forks[philo_pos];
	}
}
// forks = mutexes
void init_philo(t_info *info)
{
	int i;
	t_philo *philo;

	i = 0;
	while (i++ < info->nmb_philo)
	{
		philo = info->philos + i;
		philo->id = i + 1;
		philo->full = false;
		philo->meals_counter = 0;
		init_forks(philo, philo->forks, i); // i position in the table
	}
}

void initialize(t_info *info)
{
	int i;

	i = 0;
	// info->start_simulation = false;
	// info->all_threads_ready = false; // added its new
	info->forks = malloc(sizeof(t_fork) * info->nmb_philo);
	info->philos = malloc(sizeof(t_philo) * info->nmb_philo);
	pthread_mutex_init(info->mutex, NULL)
	while (i++ < info->nmb_philo)
	{
		pthread_mutex_init(&info->forks[i].fork, NULL);
	}
	init_philo(info);
}

void wait_all_threads(t_info *info)
{
	// if the thread are not ready keep waiting
	while (!get_bool(&info->mutex, &info->all_threads_ready))
		;
}

// 0 - wait all the philos, synchro start
// 1 - endless loop philo
void *dinner_simu(void *data)
{
	t_philo *philo;
	philo = (t_philo *)data;

	wait_all_threads(philo->infos);
	return (NULL);
}

void set_bool(pthread_mutex_t *mutex, bool *dest, bool value)
{
	pthread_mutex_lock(mutex);
	*dest = value;
	pthread_mutex_unlock(mutex);
}
bool get_bool(pthread_mutex_t *mutex, bool *value)
{
	bool res;

	pthread_mutex_lock(mutex);
	res = *value; // reading safe
	pthread_mutex_unlock(mutex);
	return (ret);
}
long get_long(pthread_mutex_t *mutex, long *value)
{
	long res;

	pthread_mutex_lock(mutex);
	res = *value; // reading safe
	pthread_mutex_unlock(mutex);
	return (ret);
}

// 0 - if no meals return 0
// 0.1 - if only one philo do hoc funtion
// 1 - create all the threads (philos)
// 2 - create a monitor thread (searching if a philo is dead)
// 3 - synchronize , make all philos start at the same time
// 4 - join everything
void start_eating(t_info *info)
{
	int i;

	i = 0;
	if (info->nmb_philo == 1)
		// do
	else if (info->limit_meals == 0)
		return ; // back to main clean
	else
	{
		while (i++ < info->nmb_philo)
			pthread_create(&info->philos[i].id, dinner_simu, &info->philos[i], NULL)
	}
	// start of simulation (need a function that is gonna give us the actual time)
	// now all threads are ready
	set_bool(&info->mutex, &info->all_threads_ready, true);

}

int check_args(int ac, char **av)
{
	if (ac < 5 || ac > 6)
		return (printf("try this"));
}

int main(int ac, char **av)
{
	t_info infos;

	if (check_args(ac, av))
		return (1);
	check_inputs(&infos, av); // error check, fill infos
	initialize(&infos);
	start_eating(&infos);
	clean(&infos); // we reach it when : philos full OR 1 philo died

}































bool check_death(t_philo *philo)
{
    long current;
    long time_since_last_meal;

    current = current_time();
    pthread_mutex_lock(&philo->infos->mutex);
    time_since_last_meal = current - philo->last_meal_time;
    if (time_since_last_meal >= philo->infos->time_die && !philo->philo_full)
    {
        philo->infos->end_simulation = true;
        printf("(%ld) %d died\n", current - philo->infos->start_simulation, philo->id);
        pthread_mutex_unlock(&philo->infos->mutex);
        return (true);
    }
    pthread_mutex_unlock(&philo->infos->mutex);
    return (false);
}

void *dinner_simu(void *data)
{
    t_philo *philo = (t_philo *)data;
    
    // Initialize last meal time
    philo->last_meal_time = philo->infos->start_simulation;
    
    while (1)
    {
        // Check if simulation should end
        if (get_bool(&philo->infos->mutex, &philo->infos->end_simulation))
            break;
            
        // Take forks
        pthread_mutex_lock(philo->left_fork);
        print_state(philo, "has taken a fork");
        pthread_mutex_lock(philo->right_fork);
        print_state(philo, "has taken a fork");
        
        // Eating
        print_state(philo, "is eating");
        pthread_mutex_lock(&philo->infos->mutex);
        philo->last_meal_time = current_time();
        pthread_mutex_unlock(&philo->infos->mutex);
        
        usleep(philo->infos->time_eat * 1000); // Convert ms to μs
        
        // Update meal count
        safe_increment(&philo->infos->mutex, &philo->meals_counter);
        
        // Release forks
        pthread_mutex_unlock(philo->left_fork);
        pthread_mutex_unlock(philo->right_fork);
        
        // Check if philosopher has eaten enough
        if (philo->infos->limit_meals > 0 && 
            philo->meals_counter >= philo->infos->limit_meals)
        {
            philo->philo_full = true;
            break;
        }
        
        // Sleeping
        print_state(philo, "is sleeping");
        usleep(philo->infos->time_sleep * 1000); // Convert ms to μs
        
        // Thinking
        print_state(philo, "is thinking");
        
        // Check death periodically (small delay to not overload CPU)
        usleep(1000); // 1ms delay between checks
        if (check_death(philo))
            break;
    }
    return (NULL);
}

void *monitor(void *data)
{
    t_info *info = (t_info *)data;
    int i;
    bool all_full;
    
    while (1)
    {
        i = 0;
        all_full = true;
        while (i < info->nmb_philo)
        {
            if (check_death(&info->philos[i]))
                return (NULL);
            if (info->limit_meals > 0 && !info->philos[i].philo_full)
                all_full = false;
            i++;
        }
        if (all_full && info->limit_meals > 0)
        {
            pthread_mutex_lock(&info->mutex);
            info->end_simulation = true;
            pthread_mutex_unlock(&info->mutex);
            return (NULL);
        }
        usleep(1000); // Check every 1ms
    }
}











