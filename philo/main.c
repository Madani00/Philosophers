#include "philo.h"

int ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
// 2147483648
// ifd fd
int num_length(char *str)
{
	int len;

	len = ft_strlen(str);
	if (len > 10)
		return (1);
	else if (len < 10)
		return (0);
	if (strncmp(str, "2147483648", 10) >= 0)
		return (1);
	return (0);

}

int is_space(char *str)
{
	return ((*str == 32) || (*str >= 9 && *str <= 13));
}

int	ft_isnum(char *str)
{
	int	i;

	i = 0;
	while (is_space(str)) // not important
		str++;
	if (str[i] == '+')
		i++;
	if (num_length(&str[i]))
		return (1);
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (1);
		i++;
	}
	return (0);
}

long	ft_atoi(const char *str)
{
	int	op;
	long	final;

	op = 1;
	final = 0;
	while ((*str == 32) || (*str >= 9 && *str <= 13))
		str++;
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

int check_numeric(int ac, char **av)
{
	int i;

	i = 1;
	while(i < ac)
	{
		if (ft_isnum(av[i])) // ft_atoi(av[i]) <= 0  redundent idiot
			return (1);
		i++;
	}
	return (0);
}
int check_args(int ac, char **av)
{
	if (ac < 5 || ac > 6)
		return (printf("Number of arguments not valid\n"));
	if (check_numeric(ac, av))
		return (printf("Error in the number\n"));
	return (0);
}

void check_inputs(t_info *info, char **av)
{
	info->nmb_philo = ft_atoi(av[1]);
	info->time_die = ft_atoi(av[2]);
	info->time_sleep = ft_atoi(av[3]);
	info->time_eat = ft_atoi(av[4]);
	info->limit_meals = -1;
	if (av[5])
		info->limit_meals = ft_atoi(av[5]);
}

// right fork = philo_id - 1 (philo position in the array) = 4
// left fork = [philo_position + 1] % philo_nmb = [4 + 1] % 5 = 0



// 1 - // [philo_pos = 0, philo->id = 1]  // [ l=(f) , r=(f) ,f ,f ,f]
// 2 - // [philo_pos = 1, philo->id = 2]  // [ f , r=(f) , l=(f) ,f ,f]
// 3 - // [philo_pos = 2, philo->id = 3]  // [ f, f , l=(f) , r=(f) ,f]
// 4 - // [philo_pos = 3, philo->id = 4]  // [ f , f , f , r=(f) , l=(f)]
// 5 - // [philo_pos = 4, philo->id = 5]  // [ r=(f) , f ,f ,f ,l=(f)]
void init_forks(t_philo *philo, pthread_mutex_t *forks, int philo_pos)
{
	int philo_nb;

	philo_nb = philo->infos->nmb_philo;     
	// deadlock problem here
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


void init_philo(t_info *info, t_philo *philo)
{
	int i;

	i = 0;
	while (i < info->nmb_philo)
	{
		philo[i].infos = info;
		philo[i].id = i + 1;
		philo[i].philo_full = false;
		philo[i].meals_counter = 0;
        
		init_forks(&philo[i], info->forks, i); // i position in the table , [f, f ,f ,f ,f]
		i++;
	}
}

void initialize(t_info *info, t_philo *philos)
{
	int i;

	i = 0;
	// info->start_simulation = 0;h
	// info->all_threads_ready = false; // added its new
	info->forks = malloc(sizeof(pthread_mutex_t) * info->nmb_philo);
	philos = malloc(sizeof(t_philo) * info->nmb_philo);
	if (!info->forks || philos)
		return ;
	pthread_mutex_init(&info->mutex, NULL);
	while (i < info->nmb_philo)
	{
		pthread_mutex_init(&info->forks[i], NULL);
		i++;
	}
	init_philo(info, philos);
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
void start_eating(t_philo *philos)
{
	int i;

	i = 0;
	
		while (i++ < philos->infos->nmb_philo)
			pthread_create(&philos[i].id, NULL, dinner_simu, &philos[i]);
	
	// start of simulation (need a function that is gonna give us the actual time)
	// now all threads are ready
	set_bool(&info->mutex, &info->all_threads_ready, true);

}

int main(int ac, char **av)
{
	t_info infos;
	t_philo philos;

	memset(&infos, 0, sizeof(t_info));

	if (check_args(ac, av))
		return (1);
	check_inputs(&infos, av);
	initialize(&infos, &philos);
	start_eating(&philos);
}









