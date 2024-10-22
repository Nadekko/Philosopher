/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andjenna <andjenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:36:34 by andjenna          #+#    #+#             */
/*   Updated: 2024/10/19 18:40:37 by andjenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	ft_usleep(int time, t_philo *philo)
{
	int	start;

	start = get_time_ms();
	while (get_time_ms() - start < time)
	{
		if (ft_check_death(philo))
			break ;
		usleep(time / 10);
	}
}

int	get_time_ms(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_print_msg(t_philo *philo, char *msg)
{
	int	time;

	time = get_time_ms() - philo->prog->start;
	pthread_mutex_lock(&philo->prog->print);
	printf("%d %d %s\n", time, philo->id, msg);
	pthread_mutex_unlock(&philo->prog->print);
}
