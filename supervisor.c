/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andjenna <andjenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:39:24 by andjenna          #+#    #+#             */
/*   Updated: 2024/10/19 19:06:40 by andjenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	ft_set_death(t_philo *philo)
{
	int	time;

	pthread_mutex_lock(&philo->prog->data);
	time = get_time_ms();
	if (time - philo->last_meal >= philo->prog->time_to_die)
	{
		philo->death = 1;
		pthread_mutex_unlock(&philo->prog->data);
		return (1);
	}
	pthread_mutex_unlock(&philo->prog->data);
	return (0);
}

void	*ft_supervisor_routine(void *args)
{
	t_prog	*prog;
	int		i;
	int		current_time;

	current_time = get_time_ms();
	prog = (t_prog *)args;
	while (1)
	{
		i = 0;
		while (i < prog->nb_of_philo)
		{
			if (ft_set_death(&prog->philo[i]))
			{
				ft_print_msg(&prog->philo[i], "died");
				return (NULL);
			}
			i++;
		}
		if (ft_check_death(prog->philo))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}

void	ft_create_supervisor(pthread_t *supervisor, t_prog prog)
{
	if (pthread_create(supervisor, NULL, ft_supervisor_routine, &prog))
	{
		printf("Error: pthread_create failed\n");
		ft_free(&prog);
		return ;
	}
	if (pthread_join(*supervisor, NULL) != 0)
	{
		printf("Error: pthread_join failed\n");
		ft_free(&prog);
		return ;
	}
}
