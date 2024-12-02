/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andjenna <andjenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 17:37:27 by andjenna          #+#    #+#             */
/*   Updated: 2024/12/02 17:37:33 by andjenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_check_nb_eaten(t_philo *philo)
{
	if (philo->prog->nb_time_to_eat == -1)
		return (0);
	if (philo->nb_eaten >= philo->prog->nb_time_to_eat)
	{
		philo->prog->nb_has_eaten++;
		if (philo->prog->nb_has_eaten == philo->prog->nb_of_philo)
		{
			ft_clean_sem(philo->prog);
			exit(0);
		}
	}
	return (0);
}

int	ft_check_death(t_philo *philo)
{
	if (get_time_ms() - philo->last_meal >= philo->prog->time_to_die)
	{
		sem_post(philo->prog->death);
		ft_clean_sem(philo->prog);
		exit(0);
	}
	return (0);
}
