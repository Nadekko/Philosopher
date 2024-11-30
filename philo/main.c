/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andjenna <andjenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 13:43:05 by andjenna          #+#    #+#             */
/*   Updated: 2024/11/25 23:48:24 by andjenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_join(t_philo *philo, t_prog *prog, pthread_t supervisor)
{
	int	i;

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
	if (pthread_join(supervisor, NULL) != 0)
	{
		printf("Error: pthread_join failed\n");
		ft_free(prog);
		return ;
	}
}

void	start_simulation(t_philo *philo, t_prog *prog, pthread_t *supervisor)
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
	if (pthread_create(supervisor, NULL, ft_supervisor_routine, prog))
	{
		printf("Error: pthread_create failed\n");
		ft_free(prog);
		return ;
	}
	ft_join(philo, prog, *supervisor);
}

static int	ft_parse_args(int ac, char **av)
{
	if (ac < 5 || ac > 6)
	{
		printf("Error : wrong number of arguments\n");
		return (1);
	}
	else if (ft_parse_params(ac, av))
		return (1);
	return (0);
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
	prog.start = get_time_ms();
	philo->last_meal = prog.start;
	start_simulation(philo, &prog, &supervisor);
	ft_free(&prog);
	return (0);
}
