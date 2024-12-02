/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andjenna <andjenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:44:45 by andjenna          #+#    #+#             */
/*   Updated: 2024/12/02 17:30:46 by andjenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_death(t_philo *philo)
{
	if (get_value(&philo->prog->death, &philo->prog->data) == 1)
		return (1);
	return (0);
}

int	ft_check_has_eaten(t_philo *philo)
{
	if (philo->prog->nb_time_to_eat != -1)
	{
		if (get_value(&philo->prog->has_eaten,
				&philo->prog->data) == philo->prog->nb_time_to_eat)
			return (1);
	}
	return (0);
}

static int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void	ft_print_msg(t_philo *philo, char *msg)
{
	int	time;

	time = get_time_ms() - philo->prog->start;
	if (ft_check_death(philo) == 1 || ft_check_has_eaten(philo) == 1)
		return ;
	pthread_mutex_lock(&philo->prog->print);
	if (!ft_strcmp(msg, "is eating"))
		printf("%s%d %d %s%s\n", YELLOW, time, philo->id, msg, RESET);
	else
		printf("%d %d %s\n", time, philo->id, msg);
	pthread_mutex_unlock(&philo->prog->print);
}

void	ft_free(t_prog *prog)
{
	int	i;

	i = 0;
	while (i < prog->nb_of_philo)
	{
		pthread_mutex_destroy(&prog->philo[i].l_fork);
		i++;
	}
	pthread_mutex_destroy(&prog->print);
	pthread_mutex_destroy(&prog->data);
	free(prog->philo);
}
