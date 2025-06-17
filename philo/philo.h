/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamchart <eamchart@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 17:35:26 by eamchart          #+#    #+#             */
/*   Updated: 2025/06/17 20:06:15 by eamchart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <errno.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_info
{
	int				nmb_philo;
	long			time_die;
	long			time_sleep;
	long			time_eat;
	long			limit_meals;
	long			start_simulation;
	bool			end_simulation;
	pthread_mutex_t	mutex;
	pthread_mutex_t	*forks;
	//bool threads_ready;     // added this
}	t_info;

typedef struct s_philo
{
	int				id;
	long			meals_counter;
	long			last_meal_time;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_t		thread_id;
	t_info			*infos;
}	t_philo;

int		ft_strlen(char *str);
long	ft_atoi(const char *str);
int		ft_isnum(char *str);
int		is_space(char *str);
int		num_length(char *str);
int		check_args(int ac, char **av);
int		check_inputs(t_info *info, char **av);
int		check_numeric(int ac, char **av);
void	init_forks(t_philo *philo, pthread_mutex_t *forks, int philo_pos);
void	init_philo(t_info *info, t_philo *philo);
void	thinking(t_philo *philo);
void	sleeping(t_philo *philo);
void	eating(t_philo *philo);
void	*thread_routine(void *data);
int		start_eating(t_philo *philos, t_info *info);
long	get_long(pthread_mutex_t *mutex, long *value);
bool	get_bool(pthread_mutex_t *mutex, bool *value);
long	current_time(void);
void	set_bool(pthread_mutex_t *mutex, bool *dest, bool value);
void	print_state(t_philo *philo, char *state);
void	*monitor_routine(void *data);
bool	check_death(t_philo *philo);
void	exact_sleep(t_info *info, long temp);

// void wait_all_threads(t_info *info); //


#endif
