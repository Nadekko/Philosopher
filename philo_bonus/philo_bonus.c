/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andjenna <andjenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 13:31:17 by andjenna          #+#    #+#             */
/*   Updated: 2024/12/17 19:01:51 by andjenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_sleep(t_philo *philo)
{
	if (!ft_check_nb_eaten(philo) || !ft_check_death(philo))
		return ;
	if (philo->prog->death->__align > 0)
		return ;
	ft_print_msg(philo, "is sleeping");
	ft_usleep(philo->prog->time_to_sleep, philo);
}

void	ft_think(t_philo *philo)
{
	int	time;

	time = 0;
	if (!ft_check_nb_eaten(philo) || !ft_check_death(philo))
		return ;
	if (philo->prog->death->__align > 0)
		return ;
	ft_print_msg(philo, "is thinking");
	time = philo->prog->time_to_eat / 2;
	ft_usleep(time, philo);
}

void	ft_eat(t_philo *philo)
{
	if (!ft_check_nb_eaten(philo) || !ft_check_death(philo))
		return ;
	if (philo->prog->death->__align > 0)
		return ;
	sem_wait(philo->prog->forks);
	sem_wait(philo->prog->forks);
	if (!ft_check_death(philo))
		return ;
	if (philo->prog->death->__align > 0)
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
	else
		usleep(500);
	while (ft_check_death(philo) == 1 && ft_check_nb_eaten(philo) == 1)
	{
		if (philo->prog->death->__align > 0)
			break ;
		if (philo->prog->nb_of_philo == 1)
		{
			sem_wait(philo->prog->forks);
			ft_print_msg(philo, "has taken a fork");
			while (ft_check_death(philo))
				;
			break ;
		}
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo);
	}
	ft_clean_sem(philo->prog);
	free(philo->prog->philo);
	exit(0);
}
