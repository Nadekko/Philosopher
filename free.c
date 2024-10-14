/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andjenna <andjenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:44:45 by andjenna          #+#    #+#             */
/*   Updated: 2024/10/14 15:45:02 by andjenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

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
