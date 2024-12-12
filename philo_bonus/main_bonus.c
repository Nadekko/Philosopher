/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andjenna <andjenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 13:31:05 by andjenna          #+#    #+#             */
/*   Updated: 2024/12/12 22:23:42 by andjenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	monitor_processes(t_philo *philo, t_prog *prog)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while (i < prog->nb_of_philo)
	{
		waitpid(philo[i].pid, &status, 0);
		if (WIFEXITED(status) == 1 && WEXITSTATUS(status) == 0)
		{
			if (prog->death->__align != 1)
			{
				// printf("%s%d %d %s%s\n", PURPLE, get_time_ms()
				// 	- philo->prog->start, philo[i].id, "died", RESET);
				printf("%d %d %s\n", get_time_ms() - philo->prog->start, philo->id, "died");
			}
			terminate_process(prog);
			break ;
		}
		i++;
	}
}

static void	start_simulation(t_philo *philo, t_prog *prog)
{
	int	i;

	i = 0;
	while (i < prog->nb_of_philo)
	{
		philo[i].pid = fork();
		if (philo[i].pid == -1)
		{
			printf("Error : fork failed\n");
			ft_clean_sem(prog);
			while (i--)
				kill(philo[i].pid, SIGKILL);
			return ;
		}
		else if (philo[i].pid == 0)
			ft_routine(&philo[i]);
		usleep(1000);
		i++;
	}
	monitor_processes(philo, prog);
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

void	ft_clean_sem(t_prog *prog)
{
	sem_close(prog->forks);
	sem_close(prog->print);
	sem_close(prog->death);
	sem_unlink("forks");
	sem_unlink("print");
	sem_unlink("death");
}

int	main(int ac, char **av)
{
	t_prog	prog;
	t_philo	*philo;

	if (ft_parse_args(ac, av) || ft_init_prog(&prog, ac, av))
		return (1);
	philo = malloc(sizeof(t_philo) * prog.nb_of_philo);
	if (!philo)
	{
		printf("Error : malloc failed\n");
		ft_clean_sem(&prog);
		return (1);
	}
	ft_init_philo(philo, &prog);
	prog.philo = philo;
	prog.start = get_time_ms();
	philo->last_meal = prog.start;
	start_simulation(philo, &prog);
	free(philo);
	return (0);
}
