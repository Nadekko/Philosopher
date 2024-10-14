/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andjenna <andjenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 13:43:05 by andjenna          #+#    #+#             */
/*   Updated: 2024/10/14 17:38:46 by andjenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

// ./philosoher nb_of_philo time_to_die 
// time_to_eat time_to_sleep 
// [nb_of_time_each_philo_must_eat]

int	ft_set_death(t_philo *philo)
{
	if (philo->last_meal > philo->prog->time_to_die)
	{
		pthread_mutex_lock(&philo->prog->data);
		philo->death = 1;
		pthread_mutex_unlock(&philo->prog->data);
		return (1);
	}
	return (0);
}

void	start_simulation(t_philo *philo, t_prog *prog, pthread_t *supervisor)
{
	int	i;

	(void)supervisor;
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

void	ft_create_supervisor(pthread_t *supervisor, t_prog prog)
{
	if (pthread_create(supervisor, NULL, ft_supervisor_routine, &prog))
	{
		printf("Error: pthread_create failed\n");
		ft_free(&prog);
		return ;
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
	// ft_create_supervisor(&supervisor, prog);
	start_simulation(philo, &prog, &supervisor);
	ft_free(&prog);
	return (0);
}
