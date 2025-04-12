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

//           ms   ms  ms
// ./philo 5 800 200 200
void check_inputs(t_info *info, char **av)
{
	info->nmb_philo = ft_atoi(av[1]); // ft_atoi make it long
	info->time_die = ft_atoi(av[2]); // ft_atoi(av[2]) * 1000 or 1e3 (to convert the milisecond to microsend )
	info->time_sleep = ft_atoi(av[3]);
	info->time_eat = ft_atoi(av[4]);
	info->limit_meals = -1;
	if (av[5])
		info->limit_meals = ft_atoi(av[5]);
}

// right fork = philo_id - 1 (philo position in the array) = 4
// left fork = [philo_position + 1] % philo_nmb = [4 + 1] % 5 = 0
// void init_forks(t_philo *philo, pthread_mutex_t *forks, int philo_pos)
// {
// 	int philo_nb;

// 	philo_nb = philo[0].infos.nmb_philo;
// 	// deadlock problem here

// 	if (philo->id % 2 == 0)
// 	{
// 		philo->right_fork = &forks[philo_pos];
// 		philo->left_fork = &forks[(philo_pos + 1) % philo_nb];
// 	}
// 	else
// 	{
// 		philo->right_fork = &forks[(philo_pos + 1) % philo_nb];
// 		philo->left_fork = &forks[philo_pos];
// 	}
// }
// forks = mutexes
void init_philo(t_info *info)
{
	int i;
	//t_philo *philo;

	i = 0;
	while (i < info->nmb_philo)
	{//  infos pointer to the address of the single t_info instance.
		// philo[i].infos = info;
		// philo[i].id = i + 1;
		// philo[i].philo_full = false;
		// philo[i].meals_counter = 0;
		info->philos[i].infos = info;
        info->philos[i].id = i + 1;
        info->philos[i].philo_full = false;
        info->philos[i].meals_counter = 0;
		//init_forks(philo, info->forks, i); // i position in the table
		i++;
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
	pthread_mutex_init(&info->mutex, NULL);
	while (i++ < info->nmb_philo)
	{
		pthread_mutex_init(&info->forks[i], NULL);
	}
	init_philo(info);
}

int main(int ac, char **av)
{
	t_info infos;

	if (check_args(ac, av))
		return (1);
	check_inputs(&infos, av); // error check, fill infos
	initialize(&infos);
}










