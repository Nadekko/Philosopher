/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andjenna <andjenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:36:34 by andjenna          #+#    #+#             */
/*   Updated: 2024/10/14 17:39:43 by andjenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	ft_printf_debug(t_prog *prog)
{
	int	i;

	printf("start: %d\n", prog->start);
	printf("death: %d\n", prog->death);
	i = 0;
	while (i < prog->nb_of_philo)
	{
		printf("philo id: %d\n", prog->philo[i].id);
		printf("philo death: %d\n", prog->philo[i].death);
		printf("philo has_eaten: %d\n", prog->philo[i].has_eaten);
		printf("philo last_meal: %d\n", prog->philo[i].last_meal);
		i++;
	}
}

void	ft_usleep(int time)
{
	int	start;

	start = get_time_ms();
	while (get_time_ms() - start < time)
		usleep(time / 10);
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
