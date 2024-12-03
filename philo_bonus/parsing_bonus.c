/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andjenna <andjenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 13:31:11 by andjenna          #+#    #+#             */
/*   Updated: 2024/12/03 13:31:14 by andjenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	is_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

long	ft_atol(char *str)
{
	long	nbr;
	int		neg;

	nbr = 0;
	neg = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			neg *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		nbr = nbr * 10 + (*str - 48);
		str++;
	}
	return (neg * nbr);
}

int	ft_print_error(char **av, int nb_of_philo, int time_each_philo_eat)
{
	if (nb_of_philo > 200)
		printf("Error : too many philosophers\n");
	else if (nb_of_philo < 1)
		printf("Error : not enough philosophers\n");
	else if (av[5] && time_each_philo_eat < 1)
	{
		printf("Error : number of time each philosopher");
		printf(" must eat must be at least 1\n");
	}
	else
		printf("Error : time must be at least 60ms\n");
	return (1);
}

int	ft_check_params(char **av)
{
	long	nb_of_philo;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	time_each_philo_eat;

	nb_of_philo = ft_atol(av[1]);
	time_to_die = ft_atol(av[2]);
	time_to_eat = ft_atol(av[3]);
	time_to_sleep = ft_atol(av[4]);
	if (av[5])
		time_each_philo_eat = ft_atol(av[5]);
	else
		time_each_philo_eat = 0;
	if (nb_of_philo < 1 || nb_of_philo > 200 || time_to_die < 60
		|| time_to_eat < 60 || time_to_sleep < 60 || (av[5]
			&& time_each_philo_eat < 1))
		return (ft_print_error(av, nb_of_philo, time_each_philo_eat));
	return (0);
}

int	ft_parse_params(int ac, char **av)
{
	int	i;
	int	nb;

	i = 1;
	while (i < ac)
	{
		nb = ft_atol(av[i]);
		if (!is_digit(av[i]))
		{
			printf("Error : wrong argument\n");
			return (1);
		}
		else if (nb <= 0 || nb > INT_MAX)
		{
			printf("Error : argument out of range\n");
			return (1);
		}
		else if (ft_check_params(av))
			return (1);
		i++;
	}
	return (0);
}
