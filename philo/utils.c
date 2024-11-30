/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andjenna <andjenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:36:34 by andjenna          #+#    #+#             */
/*   Updated: 2024/11/30 20:15:40 by andjenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_value(int *value, pthread_mutex_t *data)
{
	int	ret;

	pthread_mutex_lock(data);
	ret = *value;
	pthread_mutex_unlock(data);
	return (ret);
}

void	set_value(int *value, int new_value, pthread_mutex_t *data)
{
	pthread_mutex_lock(data);
	*value = new_value;
	pthread_mutex_unlock(data);
}

void	ft_usleep(int time, t_philo *philo)
{
	int	start;

	start = get_time_ms();
	while (get_time_ms() - start < time)
	{
		if (ft_check_death(philo) == 1)
			break ;
		usleep(100);
	}
}

int	get_time_ms(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}
