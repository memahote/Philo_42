/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memahote <memahote@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 02:10:54 by memahote          #+#    #+#             */
/*   Updated: 2023/11/24 19:49:22 by memahote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo(t_philo *philos, pthread_mutex_t *forks, t_data *data, \
					char **av)
{
	int	i;

	i = -1;
	while (++i < philo_atoi(av[1]))
	{
		philos[i].id = i + 1;
		philos[i].nb_philo = philo_atoi(av[1]);
		philos[i].t_to_die = philo_atoi(av[2]);
		philos[i].t_to_eat = philo_atoi(av[3]);
		philos[i].t_to_sleep = philo_atoi(av[4]);
		philos[i].nb_meal = -1;
		if (av[5])
			philos[i].nb_meal = philo_atoi(av[5]);
		philos[i].meal_count = 0;
		philos[i].dead = &data->dead_status;
		philos[i].time_start = get_time();
		philos[i].last_meal = get_time();
		philos[i].fork_l = &forks[i];
		philos[i].fork_r = &forks[i + 1];
		if (i == (philo_atoi(av[1]) - 1))
			philos[i].fork_r = &forks[0];
		philos[i].dead_m = &data->dead_m;
		philos[i].meal_m = &data->meal_m;
		philos[i].writing = &data->writing;
	}
}

void	init_forks(char **av, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < philo_atoi(av[1]))
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

void	init_data(t_data *data, t_philo *philo)
{
	data->dead_status = 0;
	data->philo = philo;
	pthread_mutex_init(&data->dead_m, NULL);
	pthread_mutex_init(&data->meal_m, NULL);
	pthread_mutex_init(&data->writing, NULL);
}
