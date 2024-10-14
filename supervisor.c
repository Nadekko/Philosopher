/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andjenna <andjenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:39:24 by andjenna          #+#    #+#             */
/*   Updated: 2024/10/14 17:39:50 by andjenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	get_value(int *value, pthread_mutex_t data)
{
	int	ret;

	pthread_mutex_lock(&data);
	ret = *value;
	pthread_mutex_unlock(&data);
	return (ret);
}

void	*ft_supervisor_routine(void *args)
{
	t_prog	*prog;
	int		i;

	prog = (t_prog *)args;
	i = 0;
	while (1)
	{
		get_value(&prog->philo->death, prog->data);
	}
}
