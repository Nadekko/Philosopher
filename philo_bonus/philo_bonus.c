/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andjenna <andjenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 13:31:17 by andjenna          #+#    #+#             */
/*   Updated: 2024/12/12 22:26:47 by andjenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_sleep(t_philo *philo)
{
	if (!ft_check_nb_eaten(philo) || !ft_check_death(philo))
		return;
	ft_print_msg(philo, "is sleeping");
	ft_usleep(philo->prog->time_to_sleep, philo);
}

void	ft_think(t_philo *philo)
{
	int	time;

	if (!ft_check_nb_eaten(philo) || !ft_check_death(philo))
		return;
	ft_print_msg(philo, "is thinking");
	if (philo->prog->nb_of_philo % 2 == 0)
	{
		time = philo->prog->time_to_eat / 2;
		ft_usleep(time, philo);
	}
	else
	{
		time = philo->prog->time_to_eat - philo->prog->time_to_sleep + 1;
		ft_usleep(time, philo);
	}
}

void	ft_eat(t_philo *philo)
{
	if (!ft_check_nb_eaten(philo) || !ft_check_death(philo))
		return ;
	sem_wait(philo->prog->forks);
	sem_wait(philo->prog->forks);
	if (!ft_check_death(philo))
		return ;
	ft_print_msg(philo, "has taken a fork");
	ft_print_msg(philo, "has taken a fork");
	philo->last_meal = get_time_ms();
	ft_print_msg(philo, "is eating");
	ft_usleep(philo->prog->time_to_eat, philo);
	sem_post(philo->prog->forks);
	sem_post(philo->prog->forks);
	philo->nb_eaten++;
}

void	ft_routine(t_philo *philo)
{
	if (philo->id % 2 == 0)
		usleep(1500);
	while (ft_check_death(philo) == 1 && ft_check_nb_eaten(philo) == 1)
	{
		if (philo->prog->nb_of_philo == 1)
		{
			sem_wait(philo->prog->forks);
			ft_print_msg(philo, "has taken a fork");
			while (ft_check_death(philo))
				;
		}
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo);
	}
	exit(0);
}
