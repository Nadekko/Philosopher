/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andjenna <andjenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 13:31:27 by andjenna          #+#    #+#             */
/*   Updated: 2024/12/17 19:16:55 by andjenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_check_nb_eaten(t_philo *philo)
{
	if (philo->prog->nb_time_to_eat == -1)
		return (1);
	if (philo->nb_eaten == philo->prog->nb_time_to_eat)
	{
		// printf("nb_eaten = %d\n", philo->nb_eaten);
		sem_post(philo->prog->meal_lock);
		ft_clean_sem(philo->prog);
		free(philo->prog->philo);
		exit(0);
	}
	return (1);
}

int	ft_check_death(t_philo *philo)
{
	if (get_time_ms() - philo->last_meal >= philo->prog->time_to_die)
	{
		sem_post(philo->prog->death);
		sem_wait(philo->prog->print);
		printf("%d %d %s\n", get_time_ms() - philo->prog->start, philo->id, "died");
		// printf("%d %d %s\n", get_time_ms() - philo->prog->start, philo->id, "died");
		ft_clean_sem(philo->prog);
		free(philo->prog->philo);
		exit(0);
	}
	return (1);
}


void	ft_print_msg(t_philo *philo, char *msg)
{
	int	time;

	time = get_time_ms() - philo->prog->start;
	if (!ft_check_death(philo) || !ft_check_nb_eaten(philo))
		return ;
	if (philo->prog->death->__align > 0)
		return ;
	sem_wait(philo->prog->print);
	printf("%d %d %s\n", time, philo->id, msg);
	fflush(stdout);
	sem_post(philo->prog->print);
}

// int	ft_strcmp(char *s1, char *s2)
// {
// 	int	i;

// 	i = 0;
// 	while (s1[i] && s2[i] && s1[i] == s2[i])
// 		i++;
// 	return (s1[i] - s2[i]);
// }

/*Chaque process enfant écrit sa propre sortie,
Lorsque la sortie est redirigée vers un pipe,
le mode bufferisé change(mode "block buffer"),
ce qui peut entraîner des retards ou des pertes de sorties 
si chaque processus ne vide pas explicitement son buffer.*/

// fflush(stdout);
