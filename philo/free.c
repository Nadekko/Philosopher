/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andjenna <andjenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 17:00:55 by andjenna          #+#    #+#             */
/*   Updated: 2024/12/03 17:02:32 by andjenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutex(t_prog *prog, int i)
{
	while (i > -1)
		pthread_mutex_destroy(&prog->philo[i--].l_fork);
	pthread_mutex_destroy(&prog->print);
	pthread_mutex_destroy(&prog->data);
}

void	ft_error_free(t_prog *prog, t_philo *philo, int i)
{
	while (i > -1)
		pthread_detach(philo[--i].tid);
	destroy_mutex(prog, prog->nb_of_philo - 1);
	free(philo);
}

void	ft_free(t_prog *prog)
{
	destroy_mutex(prog, prog->nb_of_philo - 1);
	free(prog->philo);
}
