/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memahote <memahote@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 20:20:22 by memahote          #+#    #+#             */
/*   Updated: 2023/11/24 19:56:31 by memahote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <limits.h>
# include <sys/time.h>

# define THREAD "ERROR : Thread creation fail"
# define THREAD2 "ERROR : Thread join fail" 
# define NB_ARGS "ERROR: The number of argments must be 4 or 5"
# define ARG1 "ERROR: There is a mistake in number of philosophers"
# define ARG2 "ERROR: There is a mistake in time to die"
# define ARG3 "ERROR: There is a mistake in time to eat"
# define ARG4 "ERROR: There is a mistake in time to sleep"
# define ARG5 "ERROR: There is a mistake in number of times each \
	philosopher must eat"

typedef struct s_philo
{
	int				id;
	int				nb_philo;
	size_t			t_to_die;
	size_t			t_to_eat;
	size_t			t_to_sleep;
	int				nb_meal;
	int				is_eating;
	int				meal_count;
	int				*dead;
	size_t			time_start;
	size_t			last_meal;
	pthread_t		thread;
	pthread_mutex_t	*fork_l;
	pthread_mutex_t	*fork_r;
	pthread_mutex_t	*writing;
	pthread_mutex_t	*dead_m;
	pthread_mutex_t	*meal_m;
}		t_philo;

typedef struct s_data
{
	int					dead_status;
	pthread_mutex_t		writing;
	pthread_mutex_t		dead_m;
	pthread_mutex_t		meal_m;
	t_philo				*philo;
}		t_data;

//parse
int		check_args(int ac, char **av);

//Init
void	init_philo(t_philo *philos, pthread_mutex_t *forks, \
					t_data *data, char **av);
void	init_forks(char **av, pthread_mutex_t *forks);
void	init_data(t_data *data, t_philo *philo);

// Utils
int		philo_atoi(char *str);
size_t	get_time(void);
int		philo_starving(t_philo *philo);

//action
void	philo_eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	philo_think(t_philo *philo);

void	*host(void *pointer);
void	print_message(char *message, t_philo *philos, int id);
void	clean(t_philo *philo, t_data *data, pthread_mutex_t *forks, char *str);
void	*routine(void *arg);
int		parse(int ac, char **av);
int		death_status(t_philo *philo);

int		ft_usleep(size_t milliseconds);
int		ft_strcmp(const char *s1, const char *s2);
#endif
