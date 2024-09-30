/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andjenna <andjenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 03:31:11 by andjenna          #+#    #+#             */
/*   Updated: 2024/09/26 05:58:19 by andjenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	init_mutex(t_prog *prog)
{
	int	i;

	i = 0;
	prog->philo->fork = malloc(sizeof(pthread_mutex_t) * prog->nb_of_philo);
	if (!prog->philo->fork)
	{
		printf("Error : malloc failed\n");
		return ;
	}
	while (i < prog->nb_of_philo)
	{
		pthread_mutex_init(&prog->philo->fork[i], NULL);
		i++;
	}
}

t_philo	*init_philo(char **av)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
	{
		printf("Error : malloc failed\n");
		return (NULL);
	}
	philo->tid = -1;
	philo->death = 0;
	if (av[5])
		philo->nb_time_to_eat = ft_atol(av[5]);
	else
		philo->nb_time_to_eat = -1;
	return (philo);
}

t_prog	*init_prog(char **av)
{
	t_prog	*prog;

	prog = malloc(sizeof(t_prog));
	if (!prog)
	{
		printf("Error : malloc failed\n");
		return (NULL);
	}
	prog->nb_of_philo = ft_atol(av[1]);
	prog->time_to_die = ft_atol(av[2]);
	prog->time_to_eat = ft_atol(av[3]);
	prog->time_to_sleep = ft_atol(av[4]);
	pthread_mutex_init(&prog->print, NULL);
	pthread_mutex_init(&prog->death, NULL);
	pthread_mutex_init(&prog->data_lock, NULL);
	prog->philo = init_philo(av);
	init_mutex(prog);
	return (prog);
}

void	free_prog(t_prog *prog)
{
	int	i;

	i = 0;
	while (i < prog->nb_of_philo)
	{
		pthread_mutex_destroy(&prog->philo->fork[i]);
		i++;
	}
	free(prog->philo->fork);
	free(prog->philo);
	pthread_mutex_destroy(&prog->print);
	pthread_mutex_destroy(&prog->death);
	pthread_mutex_destroy(&prog->data_lock);
	free(prog);
}

// void	free_philo(t_philo *philo, int i)
// {
	
// }
