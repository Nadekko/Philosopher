/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andjenna <andjenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 16:57:02 by andjenna          #+#    #+#             */
/*   Updated: 2024/12/02 17:23:26 by andjenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_clean_sem(t_prog *prog)
{
	sem_close(prog->forks);
	sem_close(prog->print);
	sem_close(prog->death);
	sem_unlink("forks");
	sem_unlink("print");
	sem_unlink("death");
}

void	ft_free(t_prog *prog, t_philo *philo)
{
	(void)prog;
	// ft_clean_sem(prog);
	free(philo);
}
