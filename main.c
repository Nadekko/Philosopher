/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andjenna <andjenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 13:43:05 by andjenna          #+#    #+#             */
/*   Updated: 2024/10/19 18:57:19 by andjenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

// ./philosoher nb_of_philo time_to_die
// time_to_eat time_to_sleep
// [nb_of_time_each_philo_must_eat]

void	start_simulation(t_philo *philo, t_prog *prog)
{
	int	i;

	i = 0;
	while (i < prog->nb_of_philo)
	{
		if (pthread_create(&philo[i].tid, NULL, ft_routine, &philo[i]))
		{
			printf("Error: pthread_create failed\n");
			ft_free(prog);
			return ;
		}
		i++;
	}
	i = 0;
	while (i < prog->nb_of_philo)
	{
		if (pthread_join(philo[i].tid, NULL) != 0)
		{
			printf("Error: pthread_join failed\n");
			ft_free(prog);
			return ;
		}
		i++;
	}
}

int	main(int ac, char **av)
{
	t_prog		prog;
	t_philo		*philo;
	pthread_t	supervisor;

	if (ft_parse_args(ac, av) || ft_init_prog(&prog, ac, av))
		return (1);
	philo = malloc(sizeof(t_philo) * prog.nb_of_philo);
	if (!philo)
	{
		printf("Error: malloc failed\n");
		return (1);
	}
	if (ft_init_philo(philo, &prog))
	{
		free(philo);
		return (1);
	}
	prog.philo = philo;
	start_simulation(philo, &prog);
	ft_create_supervisor(&supervisor, prog);
	ft_free(&prog);
	return (0);
}
