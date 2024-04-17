/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memahote <memahote@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 15:16:27 by memahote          #+#    #+#             */
/*   Updated: 2023/11/24 20:00:11 by memahote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_l);
	print_message("has taken a fork", philo, philo->id);
	if (philo->nb_philo == 1)
	{
		ft_usleep(philo->t_to_die);
		pthread_mutex_unlock(philo->fork_l);
		return ;
	}
	pthread_mutex_lock(philo->fork_r);
	print_message("has taken a fork", philo, philo->id);
	print_message("is eating", philo, philo->id);
	pthread_mutex_lock(philo->meal_m);
	philo->last_meal = get_time();
	philo->meal_count++;
	pthread_mutex_unlock(philo->meal_m);
	ft_usleep((philo->t_to_eat));
	pthread_mutex_unlock(philo->fork_l);
	pthread_mutex_unlock(philo->fork_r);
}

void	philo_sleep(t_philo *philo)
{
	print_message("is sleeping", philo, philo->id);
	ft_usleep((philo->t_to_sleep));
}

void	philo_think(t_philo *philo)
{
	print_message("is thinking ...", philo, philo->id);
}

int	death_status(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_m);
	if (*philo->dead == 1)
		return (pthread_mutex_unlock(philo->dead_m), 1);
	return (pthread_mutex_unlock(philo->dead_m), 0);
}

void	*routine(void *pointer)
{
	t_philo	*philo;

	philo = pointer;
	if ((philo->id % 2) == 0)
		ft_usleep(40);
	while (!death_status(philo))
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (pointer);
}
