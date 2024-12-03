/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andjenna <andjenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 17:00:55 by andjenna          #+#    #+#             */
/*   Updated: 2024/12/03 18:52:03 by andjenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutex(t_prog *prog, int i)
{
	int j;

	j = 0;
	while (j > i)
		pthread_mutex_destroy(&prog->philo[j++].l_fork);
	pthread_mutex_destroy(&prog->print);
	pthread_mutex_destroy(&prog->data);
}

void	ft_error_free(t_philo *philo, int i)
{
	int j;

	j = 0;
	while (j > i)
		pthread_detach(philo[j++].tid);
}

void	ft_free(t_prog *prog)
{
	destroy_mutex(prog, prog->nb_of_philo);
	free(prog->philo);
}
