/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andjenna <andjenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:36:10 by andjenna          #+#    #+#             */
/*   Updated: 2024/10/14 16:08:40 by andjenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	ft_sleep(t_philo *philo)
{
	pthread_mutex_unlock(&philo->prog->data);
	ft_print_msg(philo, "is sleeping");
	pthread_mutex_unlock(&philo->prog->data);
	ft_usleep(philo->prog->time_to_sleep);
	return (0);
}

int	ft_eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
		ft_usleep(500);
	pthread_mutex_lock(&philo->l_fork);
	ft_print_msg(philo, "has taken a fork");
	pthread_mutex_lock(philo->r_fork);
	ft_print_msg(philo, "has taken a fork");
	pthread_mutex_lock(&philo->prog->data);
	philo->last_meal = get_time_ms() - philo->prog->start;
	ft_print_msg(philo, "is eating");
	pthread_mutex_unlock(&philo->prog->data);
	ft_usleep(philo->prog->time_to_eat);
	philo->has_eaten++;
	pthread_mutex_unlock(&philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	return (0);
}

void	*ft_routine(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	while (1)
	{
		if (ft_set_death(philo))
		{
			ft_print_msg(philo, "died");
			break ;
		}
		ft_eat(philo);
		if (get_value(&philo->has_eaten, philo->prog->data) > 0)
			ft_sleep(philo);
	}
	return (NULL);
}
