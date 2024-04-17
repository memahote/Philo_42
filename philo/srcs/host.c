/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   host.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memahote <memahote@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 18:36:33 by memahote          #+#    #+#             */
/*   Updated: 2023/11/24 19:48:18 by memahote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_starving(t_philo *philo)
{
	pthread_mutex_lock(philo->meal_m);
	if (get_time() - philo->last_meal >= philo->t_to_die)
		return (pthread_mutex_unlock(philo->meal_m), 1);
	return (pthread_mutex_unlock(philo->meal_m), 0);
}

int	check_death(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo[0].nb_philo)
	{
		if (philo_starving(&philo[i]))
		{
			print_message("died", &philo[i], philo[i].id);
			pthread_mutex_lock(philo[0].dead_m);
			*philo->dead = 1;
			pthread_mutex_unlock(philo[0].dead_m);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_if_all_ate(t_philo *philo)
{
	int	i;
	int	finished_eating;

	i = 0;
	finished_eating = 0;
	if (philo[0].nb_meal == -1)
		return (0);
	while (i < philo[0].nb_philo)
	{
		pthread_mutex_lock(philo[i].meal_m);
		if (philo[i].meal_count >= philo[i].nb_meal)
			finished_eating++;
		pthread_mutex_unlock(philo[i].meal_m);
		i++;
	}
	if (finished_eating == philo[0].nb_philo)
	{
		pthread_mutex_lock(philo[0].dead_m);
		*philo->dead = 1;
		pthread_mutex_unlock(philo[0].dead_m);
		return (1);
	}
	return (0);
}

void	*host(void	*pointer)
{
	t_philo	*philo;

	philo = pointer;
	while (1)
		if (check_death(philo) == 1 || check_if_all_ate(philo) == 1)
			break ;
	return (pointer);
}
