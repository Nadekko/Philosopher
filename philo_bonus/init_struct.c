/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andjenna <andjenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:23:12 by andjenna          #+#    #+#             */
/*   Updated: 2024/12/02 17:25:00 by andjenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_init_sem(t_prog *prog)
{
	sem_unlink("forks");
	sem_unlink("print");
	sem_unlink("death");
	// sem_unlink("has_eaten");
	prog->forks = sem_open("forks", O_CREAT, 0644, prog->nb_of_philo);
	if (prog->forks == SEM_FAILED)
		return (printf("Error : %s\n", strerror(errno)), 1);
	prog->print = sem_open("print", O_CREAT, 0644, 1);
	if (prog->print == SEM_FAILED)
		return (printf("Error : %s\n", strerror(errno)), 1);
	prog->death = sem_open("death", O_CREAT, 0644, 1);
	if (prog->death == SEM_FAILED)
		return (printf("Error : %s\n", strerror(errno)), 1);
	// prog->has_eaten = sem_open("has_eaten", O_CREAT, 0644, 1);
	// if (prog->has_eaten == SEM_FAILED)
	// 	return (printf("Error : %s\n", strerror(errno)), 1);
	return (0);
}

int	ft_init_prog(t_prog *prog, int ac, char **av)
{
	prog->nb_of_philo = ft_atol(av[1]);
	prog->time_to_die = ft_atol(av[2]);
	prog->time_to_eat = ft_atol(av[3]);
	prog->time_to_sleep = ft_atol(av[4]);
	prog->nb_time_to_eat = -1;
	if (ac == 6)
		prog->nb_time_to_eat = ft_atol(av[5]);
	prog->start = get_time_ms();
	prog->nb_has_eaten = 0;
	prog->death_flag = 0;
	if (ft_init_sem(prog))
		return (1);
	return (0);
}

int	ft_init_philo(t_philo *philo, t_prog *prog)
{
	int	i;

	i = 0;
	while (i < prog->nb_of_philo)
	{
		philo[i].id = i + 1;
		philo[i].last_meal = prog->start;
		philo[i].prog = prog;
		philo[i].nb_eaten = -1;
		if (prog->nb_time_to_eat != -1)
			philo[i].nb_eaten = 0;
		philo[i].death = 0;
		i++;
	}
	return (0);
}
