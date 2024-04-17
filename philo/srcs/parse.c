/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memahote <memahote@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 20:21:33 by memahote          #+#    #+#             */
/*   Updated: 2023/11/24 19:52:19 by memahote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse(int ac, char **av)
{
	if (ac != 5 && ac != 6)
	{
		printf("%s\n", NB_ARGS);
		return (0);
	}
	else if (!check_args(ac, av))
		return (0);
	return (1);
}

int	check_args(int ac, char **av)
{
	if (!philo_atoi(av[1]))
		return (printf("%s\n", ARG1), 0);
	if (!philo_atoi(av[2]))
		return (printf("%s\n", ARG2), 0);
	if (!philo_atoi(av[3]))
		return (printf("%s\n", ARG3), 0);
	if (!philo_atoi(av[4]))
		return (printf("%s\n", ARG4), 0);
	if (ac == 6)
		if (!philo_atoi(av[5]))
			return (printf("%s\n", ARG5), 0);
	return (1);
}
