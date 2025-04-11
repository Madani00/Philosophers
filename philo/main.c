#include "philo.h"



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
void init_forks(t_philo *philo, pthread_mutex_t *forks, int philo_pos)
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
		philo[i].id = i + 1;
		philo[i].full = 0;
		philo[i].meals_counter = 0;
		init_forks(philo, info->forks, i); // i position in the table
	}
}

void initialize(t_info *info)
{
	int i;

	i = 0;
	// info->start_simulation = false;
	// info->all_threads_ready = false; // added its new
	info->forks = malloc(sizeof(pthread_mutex_t) * info->nmb_philo);
	info->philos = malloc(sizeof(t_philo) * info->nmb_philo);
	pthread_mutex_init(info->mutex, NULL);
	while (i++ < info->nmb_philo)
	{
		pthread_mutex_init(&info->forks[i], NULL);
	}
	init_philo(info);
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
