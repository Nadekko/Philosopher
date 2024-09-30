/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andjenna <andjenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 13:43:05 by andjenna          #+#    #+#             */
/*   Updated: 2024/09/30 13:27:43 by andjenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

// ./philosoher nb_of_philo time_to_die time_to_eat time_to_sleep [nb_of_time_each_philo_must_eat]
// void	schedule_eat(t_prog *prog)
// {
// }

void	schedule_eat(t_prog *prog)
{
	int	i;

	i = 0;
	while (i < prog->nb_of_philo)
	{
		pthread_mutex_lock(&prog->philo->fork[i]);
		pthread_mutex_lock(&prog->philo->fork[(i + 1) % prog->nb_of_philo]);
		pthread_mutex_lock(&prog->print);
		printf("[%lu] is eating\n", prog->philo->tid);
		pthread_mutex_unlock(&prog->print);
		pthread_mutex_unlock(&prog->philo->fork[i]);
		pthread_mutex_unlock(&prog->philo->fork[(i + 1) % prog->nb_of_philo]);
		i++;
	}
	
void	*routine(void *data)
{
	t_prog	*prog;
	int		i;

	prog = (t_prog *)data;
	i = 0;
	// schedule_eat(prog);
	printf("Hello from philosopher [%lu]\n", prog->philo->tid);
	pthread_mutex_lock(&prog->philo->fork[i]);
	pthread_mutex_lock(&prog->philo->fork[(i + 1) % prog->nb_of_philo]);
	printf("%sTID [%lu] is eating (๑ᵔ⤙ᵔ๑) %s\n", CYAN, prog->philo->tid, RESET);
	pthread_mutex_unlock(&prog->philo->fork[i]);
	pthread_mutex_unlock(&prog->philo->fork[(i + 1) % prog->nb_of_philo]);
	printf("%sTID [%lu] stoped eating%s\n", PURPLE, prog->philo->tid, RESET);
	printf("Goodbye from philosopher [%lu]\n", prog->philo->tid);
	i++;
	return (NULL);
}

void	test_pthread(t_prog *prog)
{
	int	i;

	i = 1;
	while (i <= prog->nb_of_philo)
	{
		if (pthread_create(&prog->philo->tid, NULL, &routine, prog) != 0)
		{
			printf("Error : pthread_create failed\n");
			return ;
		}
		usleep(prog->time_to_eat * 1000);
		i++;
	}
	while (i > 0)
	{
		pthread_join(prog->philo->tid, NULL);
		i--;
	}
	return ;
}

int	main(int ac, char **av, char **env)
{
	t_prog	*prog;

	prog = NULL;
	if (!env)
		printf("Error : no environnement\n");
	if (ac < 5 || ac > 6)
	{
		printf("Error : wrong number of arguments\n");
		return (1);
	}
	else
	{
		if (ft_parse_params(ac, av))
			return (1);
		else
		{
			prog = init_prog(av);
			test_pthread(prog);
		}
	}
	free_prog(prog);
	return (0);
}
