/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memahote <memahote@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 22:19:30 by memahote          #+#    #+#             */
/*   Updated: 2023/11/24 19:53:11 by memahote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean(t_philo *philo, t_data *data, pthread_mutex_t *forks, char *str)
{
	int	i;

	i = 0;
	if (ft_strcmp(str, THREAD) == 0)
		printf("%s\n", THREAD);
	if (ft_strcmp(str, THREAD2) == 0)
		printf("%s\n", THREAD2);
	if (philo)
		free(philo);
	pthread_mutex_destroy(&data->dead_m);
	pthread_mutex_destroy(&data->meal_m);
	pthread_mutex_destroy(&data->writing);
	while (i < philo[0].nb_philo)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	free(forks);
	exit(1);
}

void	thread_create(t_data *data, pthread_mutex_t *forks, t_philo *philo)
{
	pthread_t	host_t;
	int			i;

	i = 0;
	if (pthread_create(&host_t, NULL, &host, data->philo) != 0)
		clean(philo, data, forks, THREAD);
	while (i < data->philo->nb_philo)
	{
		if (pthread_create(&data->philo[i].thread, NULL, &routine, \
					&data->philo[i]) != 0)
			clean(philo, data, forks, THREAD);
		i++;
	}
	if (pthread_join(host_t, NULL) != 0)
		clean(philo, data, forks, THREAD2);
	i = 0;
	while (i < data->philo[0].nb_philo)
	{
		if (pthread_join(data->philo[i].thread, NULL) != 0)
			clean(philo, data, forks, THREAD2);
		i++;
	}
}

int	main(int ac, char **av)
{
	pthread_mutex_t	*forks;
	t_philo			*philo;
	t_data			data;

	if (!parse(ac, av))
		return (0);
	forks = malloc(sizeof(pthread_mutex_t) *(philo_atoi(av[1]) + 1));
	if (!forks)
		return (0);
	philo = malloc(sizeof(t_philo) * (philo_atoi(av[1]) + 1));
	if (!philo)
		return (0);
	init_data(&data, philo);
	init_forks(av, forks);
	init_philo(philo, forks, &data, av);
	thread_create(&data, forks, philo);
	if (forks)
		free(forks);
	if (philo)
		free(philo);
}

// malloc trop grand pour les forks et philo ?
// 4 adresse de pointer pour les fork alors qu'il n'y a que 3 philo
//quand je reduis le malloc , le programme reste bloquer dna sla boucle
// de host check if dead