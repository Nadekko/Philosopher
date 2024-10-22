/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andjenna <andjenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:36:10 by andjenna          #+#    #+#             */
/*   Updated: 2024/10/22 12:50:34 by andjenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"


int	get_value(int *value, pthread_mutex_t data)
{
	int	ret;

	pthread_mutex_lock(&data);
	ret = *value;
	pthread_mutex_unlock(&data);
	return (ret);
}

int	ft_sleep(t_philo *philo)
{
	pthread_mutex_unlock(&philo->prog->data);
	ft_print_msg(philo, "is sleeping");
	pthread_mutex_unlock(&philo->prog->data);
	ft_usleep(philo->prog->time_to_sleep, philo);
	return (0);
}

int	ft_eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->l_fork);
		ft_print_msg(philo, "has taken a fork");
		pthread_mutex_lock(philo->r_fork);
		ft_print_msg(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->r_fork);
		ft_print_msg(philo, "has taken a fork");
		pthread_mutex_lock(&philo->l_fork);
		ft_print_msg(philo, "has taken a fork");
	}
	pthread_mutex_lock(&philo->prog->data);
	philo->last_meal = get_time_ms() - philo->prog->start;
	ft_print_msg(philo, "is eating");
	pthread_mutex_unlock(&philo->prog->data);
	ft_usleep(philo->prog->time_to_eat, philo);
	philo->has_eaten++;
	pthread_mutex_unlock(&philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	return (0);
}

int	ft_think(t_philo *philo)
{
	int	time_to_think;

	pthread_mutex_lock(&philo->prog->data);
	time_to_think = philo->prog->time_to_die - (philo->prog->time_to_eat - philo->prog->time_to_sleep);
	pthread_mutex_unlock(&philo->prog->data);
	ft_print_msg(philo, "is thinking");
	ft_usleep(time_to_think, philo);
	return (0);
}

int	ft_check_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->prog->data);
	if (philo->last_meal >= philo->prog->time_to_die)
	{
		ft_print_msg(philo, "died");
		philo->death = 1;
		pthread_mutex_unlock(&philo->prog->data);
		return (1);
	}
	pthread_mutex_unlock(&philo->prog->data);
	return (0);
}

void	*ft_routine(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	while (!ft_check_death(philo))
	{
		if (philo->id % 2 == 0)
			usleep(1500);
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo);
	}
	return (NULL);
}
