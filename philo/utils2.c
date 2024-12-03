/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andjenna <andjenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:44:45 by andjenna          #+#    #+#             */
/*   Updated: 2024/12/03 17:10:23 by andjenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
