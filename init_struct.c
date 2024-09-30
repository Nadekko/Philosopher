/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andjenna <andjenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 03:31:11 by andjenna          #+#    #+#             */
/*   Updated: 2024/09/30 18:12:49 by andjenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	ft_init_prog(t_prog *prog, int ac, char **av)
{
	prog->nb_of_philo = ft_atol(av[1]);
	prog->time_to_die = ft_atol(av[2]);
	prog->time_to_eat = ft_atol(av[3]);
	prog->time_to_sleep = ft_atol(av[4]);
	prog->start.tv_sec = 0;
	prog->start.tv_usec = 0;
	prog->nb_time_to_eat = -1;
	if (ac == 6)
		prog->nb_time_to_eat = ft_atol(av[5]);
	if (pthread_mutex_init(&prog->print, NULL) != 0)
	{
		printf("Error: mutex init failed\n");
		return (1);
	}
	if (pthread_mutex_init(&prog->data, NULL) != 0)
	{
		printf("Error: mutex init failed\n");
		return (1);
	}
	return (0);
}

int	ft_init_philo(t_philo *philo, t_prog *prog)
{
	int	i;

	i = 0;
	while (i < prog->nb_of_philo)
	{
		philo[i].nb_time_to_eat = prog->nb_time_to_eat;
		philo[i].has_eaten = 0;
		philo[i].last_meal = 0;
		philo[i].death = 0;
		if (prog->nb_time_to_eat != -1)
			philo[i].nb_time_to_eat = 0;
		if (pthread_mutex_init(&philo[i].l_fork, NULL) != 0)
		{
			printf("Error: mutex init failed\n");
			/*fonction qui destroy les mutex*/
			return (1);
		}
		philo[i].r_fork = philo[(i + 1) % prog->nb_of_philo].l_fork;
		i++;
	}
	return (0);
}

