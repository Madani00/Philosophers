#include "philo.h"

void clean_up(t_philo *philo, t_info *info)
{
	int i;

	i = 0;
	while (i < philo->infos->nmb_philo)
	{
		pthread_join(philo[i].thread_id, NULL);
		i++;
	}
	free(philo);
	free(info->forks);
}

void init_forks(t_philo *philo, pthread_mutex_t *forks, int philo_pos)
{
	int philo_nb;

	philo_nb = philo->infos->nmb_philo;   
	if (philo->id % 2 == 0)
	{
		philo->right_fork = &forks[philo_pos];
		philo->left_fork = &forks[(philo_pos + 1) % philo_nb];
	}
	else
	{					                                       
		philo->right_fork = &forks[(philo_pos + 1) % philo_nb];
		philo->left_fork = &forks[philo_pos];
	}
}
long get_long(pthread_mutex_t *mutex, long *value)
{
	long res;

	pthread_mutex_lock(mutex);
	res = *value;
	pthread_mutex_unlock(mutex);
	return (res);
}

void init_philo(t_info *info, t_philo *philo)
{
	int i;

	i = 0;
	while (i < info->nmb_philo)
	{
		philo[i].infos = info;
		philo[i].id = i + 1;
		philo[i].meals_counter = 0;
		init_forks(&philo[i], info->forks, i);
		i++;
	}
}

t_philo * initialize(t_info *info)
{
	int i;
	t_philo *philos;

	i = 0;
	info->forks = malloc(sizeof(pthread_mutex_t) * info->nmb_philo);
	philos = malloc(sizeof(t_philo) * info->nmb_philo);
	if (!info->forks || !philos)
		return (NULL);
	if (pthread_mutex_init(&info->mutex, NULL))
		return (NULL);
	while (i < info->nmb_philo)
	{
		if (pthread_mutex_init(&info->forks[i], NULL))
			return (NULL);
		i++;
	}
	init_philo(info, philos);
	return (philos);
}
bool get_bool(pthread_mutex_t *mutex, bool *value)
{
	bool res;

	pthread_mutex_lock(mutex);
	res = *value;
	pthread_mutex_unlock(mutex);
	return (res);
}


long	current_time(void)
{
	struct timeval	s_time;

	gettimeofday(&s_time, NULL);
	return ((s_time.tv_sec * 1000) + (s_time.tv_usec / 1000));
}


void set_bool(pthread_mutex_t *mutex, bool *dest, bool value)
{
	pthread_mutex_lock(mutex);
	*dest = value;
	pthread_mutex_unlock(mutex);
}

void print_state(t_philo *philo, char *state)
{
	long time;

	if (!get_bool(&philo->infos->mutex, &philo->infos->end_simulation))
	{
		pthread_mutex_lock(&philo->infos->mutex);
		time = current_time() - philo->infos->start_simulation;
		printf("%ld %d %s\n", time, philo->id, state);
		pthread_mutex_unlock(&philo->infos->mutex);
	}
}

void thinking(t_philo *philo)
{
	if (!get_bool(&philo->infos->mutex, &philo->infos->end_simulation))
	{
		print_state(philo, "is thinking");
		if (philo->id % 2 != 0)
			usleep(philo->infos->time_eat * 0.5);
	}
}
void sleeping(t_philo *philo)
{
	if (!get_bool(&philo->infos->mutex, &philo->infos->end_simulation))
	{
		print_state(philo, "is sleeping");
		usleep(philo->infos->time_sleep);
	}
}


void eating(t_philo *philo)
{
	if (!get_bool(&philo->infos->mutex, &philo->infos->end_simulation))
	{
		pthread_mutex_lock(philo->left_fork);
		print_state(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_state(philo, "has taken a fork");
		print_state(philo, "is eating");
		pthread_mutex_lock(&philo->infos->mutex);
		philo->last_meal_time = current_time(); 
		philo->meals_counter++;
		pthread_mutex_unlock(&philo->infos->mutex);
		if (!get_bool(&philo->infos->mutex, &philo->infos->end_simulation))
			usleep(philo->infos->time_eat);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
	
}
void *thread_routine(void *data)
{
	t_philo *philo;
	philo = (t_philo *)data;

	while (!philo->infos->end_simulation)
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

 
bool check_death(t_philo *philo)
{
    long current;
    long time_pass;
	pthread_mutex_lock(&philo->infos->mutex);

    current = current_time();
    time_pass = current - philo->last_meal_time;
    if (time_pass >= philo->infos->time_die)
    {
		//set_bool(&philo->infos->mutex, &philo->infos->end_simulation, true);
        philo->infos->end_simulation = true;
        printf("%ld %d died\n", current - philo->infos->start_simulation, philo->id);
        pthread_mutex_unlock(&philo->infos->mutex);
        return (true);
    }
    pthread_mutex_unlock(&philo->infos->mutex);
    return (false);
}

// void *monitor_routine(void *data)
// {
//     t_philo *philo = (t_philo *)data;
//     int i;
//     bool all_full;
    
//     while (1)
//     {
//         i = 0;
//         all_full = true;
// 		while (i < philo->infos->nmb_philo)
// 		{	
// 			if (get_long(&philo->infos->mutex, &philo[i].meals_counter) < philo->infos->limit_meals && philo->infos->limit_meals > 0)
// 				all_full = false;
// 			// if (check_death(&philo[i]))
// 			// 	return (NULL);
// 			i++;
// 		}
//         if (all_full && philo->infos->limit_meals > 0)
//         {
// 			set_bool(&philo->infos->mutex, &philo->infos->end_simulation, true);
//             return (NULL);
//         }
//         usleep(1000); // Check every 1ms
//     }
// }

void *monitor_routine(void *data)
{
    t_philo *philos = (t_philo *)data;
    int i;

	
    while (1)
    {
		usleep(philos->infos->time_die + 1);
        i = 0;
        while (i < philos[0].infos->nmb_philo)
        {
            if (check_death(&philos[i]))
                return NULL;
            i++;
        }
        //usleep(1000);
    }
}



int start_eating(t_philo *philos, t_info *info)
{
	int i;
	pthread_t monitor;
	i = 0;

	info->end_simulation = false;
	info->start_simulation = current_time();
	while (i < info->nmb_philo)
	{
		if (pthread_create(&philos[i].thread_id, NULL, thread_routine, &philos[i]))
			return (1);
		i++;
	}
	pthread_create(&monitor, NULL, monitor_routine, philos);
	pthread_join(monitor, NULL);
	return (0);
}


int main(int ac, char **av)
{
	t_info infos;
	t_philo *philos;

	memset(&infos, 0, sizeof(t_info));
	if (check_args(ac, av))
		return (1);
	if (check_inputs(&infos, av))
		return (printf("Error in the number\n"));
	philos = initialize(&infos);
	if (!philos)
		return (1);
	if (start_eating(philos, &infos))
		return (1);
	clean_up(philos, &infos);
}