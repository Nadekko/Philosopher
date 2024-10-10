/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andjenna <andjenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 13:43:05 by andjenna          #+#    #+#             */
/*   Updated: 2024/10/10 19:39:54 by andjenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

// ./philosoher nb_of_philo time_to_die time_to_eat time_to_sleep [nb_of_time_each_philo_must_eat]
void	ft_usleep(int time)
{
	int	start;

	start = get_time_ms();
	while (get_time_ms() - start < time)
		usleep(time / 10);
}

int	get_time_ms(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_print_msg(t_philo *philo, char *msg)
{
	int	time;

	time = get_time_ms() - philo->prog->start;
	pthread_mutex_lock(&philo->prog->print);
	printf("[%d] %d %s\n", time, philo->id, msg);
	pthread_mutex_unlock(&philo->prog->print);
}
int	ft_eat(t_philo *philo)
{
	// if (philo->id % 2 == 0)
	// 	ft_usleep(philo->prog->time_to_eat / 10);
	pthread_mutex_lock(&philo->prog->data);
	pthread_mutex_lock(&philo->l_fork);
	pthread_mutex_lock(&philo->r_fork);
	ft_print_msg(philo, "has taken fork");
	philo->last_meal = get_time_ms();
	ft_print_msg(philo, "start eating.");
	ft_usleep(philo->prog->time_to_eat);
	philo->has_eaten++;
	pthread_mutex_unlock(&philo->l_fork);
	pthread_mutex_unlock(&philo->r_fork);
	pthread_mutex_unlock(&philo->prog->data);
	return (0);
}

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
int	ft_sleep(t_philo *philo)
{
	ft_print_msg(philo, "is sleeping.");
	ft_usleep(philo->prog->time_to_sleep);
	ft_print_msg(philo, "is thinking.");
	return (0);
}
void	*ft_routine(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	while (1)
	{
		ft_eat(philo);
		ft_sleep(philo);
	}
	return (NULL);
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
			/* destory and free all*/
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
			/* destory and free all*/
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
	// ft_create_supervisor(&supervisor, philo);
	start_simulation(philo, &prog, &supervisor);
	return (0);
}

// void	*ft_supervisor_routine(void *args)
// {
// 	t_prog	*prog;
// 	int		i;

// 	prog = (t_prog *)args;
// 	i = 0;
// 	while (1)
// 	{

// 	}
// }

// void	ft_create_supervisor(pthread_t *supervisor, t_philo *philo)
// {
// 	if (pthread_create(supervisor, NULL, ft_supervisor_routine, philo))
// 	{
// 		printf("Error: pthread_create failed\n");
// 		/* destory and free all*/
// 		return ;
// 	}
// }
