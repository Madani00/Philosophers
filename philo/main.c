#include "philo.h"
//           ms   ms  ms
// ./philo 5 800 200 200
void check_inputs(t_info *info, char **av)
{
	info->nmb_philo = atoi(av[1]); // atoi make it long
	info->time_die = atoi(av[2]) * 1000; // or 1e3 (to convert the milisecond to microsend )
	info->time_sleep = atoi(av[3]) * 1000;
	info->time_eat = atoi(av[4]) * 1000;
	if (info->time_die < 60000 || info->time_eat < 60000 || info->time_sleep < 60000)
		printf("timestamps must be more than 60ms")
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

void init_infos(t_info *info)
{
	int i;

	i = 0;
	info->start_simulation = false;
	info->forks = malloc(sizeof(t_fork) * info->nmb_philo);
	info->philos = malloc(sizeof(t_philo) * info->nmb_philo);
	while (i++ < info->nmb_philo)
	{
		pthread_mutex_init(&info->forks[i].fork, NULL);
		info->forks[i].fork_id = i; // useful for debugging
	}
	init_philo(info);
}


void *dinner_simu(void *data)
{
	t_philo *philo;
	philo = (t_philo *)data;
	
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
}

long nmb_philo;
	long time_die;
	long time_sleep;
	long time_eat;
	long limit_meals; // [5] } flag if -1 then it is not provided
	long start_simulation; // all philos will have a timestamps starting from this value
	bool end_simulation; // turn on, when a philo dies or all philos are full
	t_fork *forks; // array to all forks [f, f ,f ,f ,f]
	t_philo *philos;

int main(int ac, char **av)
{
	t_info infos;

	if (ac == 5 || ac == 6)
	{
		check_inputs(&infos, av); // error check, fill infos
		initiaze_infos(&infos);
		start_eating(&infos);
		clean(&infos); // we reach it when : philos full OR 1 philo died
	}
	else
		printf("error");
}
