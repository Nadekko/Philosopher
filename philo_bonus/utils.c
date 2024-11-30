/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andjenna <andjenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:33:50 by andjenna          #+#    #+#             */
/*   Updated: 2024/11/30 20:20:46 by andjenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void ft_print_msg(t_philo *philo, char *msg)
{
	int time;

	time = get_time_ms() - philo->prog->start;
	if (ft_check_death(philo) == 1 || ft_check_nb_eaten(philo) == 1)
		return;
	sem_wait(philo->prog->print);
	printf("%d %d %s\n", time, philo->id, msg);
	sem_post(philo->prog->print);
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

void terminate_process(t_prog *prog)
{
	int i;

	i = 0;
	ft_clean_sem(prog);
	while (i < prog->nb_of_philo)
	{
		kill(prog->philo[i].pid, SIGKILL);
		i++;
	}
}
