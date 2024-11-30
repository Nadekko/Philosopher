/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andjenna <andjenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:39:24 by andjenna          #+#    #+#             */
/*   Updated: 2024/11/30 20:13:45 by andjenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_set_death(t_prog *prog)
{
	int	i;
	int	time;

	time = get_time_ms() - prog->start;
	i = 0;
	while (i < prog->nb_of_philo)
	{
		if (get_time_ms() - get_value(&prog->philo[i].last_meal,
				&prog->data) > prog->time_to_die)
		{
			set_value(&prog->death, 1, &prog->data);
			pthread_mutex_lock(&prog->print);
			printf("%s%d %d died%s\n", PURPLE, time, prog->philo[i].id, RESET);
			pthread_mutex_unlock(&prog->print);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	ft_set_nb_eaten(t_prog *prog)
{
	int	i;
	int	eaten;

	i = 0;
	eaten = 0;
	while (i < prog->nb_of_philo)
	{
		if (prog->philo[i].nb_eaten == prog->nb_time_to_eat)
		{
			eaten++;
			if (eaten == prog->nb_of_philo)
			{
				prog->has_eaten = prog->nb_time_to_eat;
				return (1);
			}
		}
		i++;
	}
	return (0);
}

void	*ft_supervisor_routine(void *args)
{
	t_prog	*prog;
	int		current_time;

	current_time = get_time_ms();
	prog = (t_prog *)args;
	while (1)
	{
		if (ft_set_death(prog))
			return (NULL);
		if (prog->nb_time_to_eat != -1)
		{
			if (ft_set_nb_eaten(prog))
				return (NULL);
		}
	}
	return (NULL);
}
