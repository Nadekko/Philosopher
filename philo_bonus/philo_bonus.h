/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andjenna <andjenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:19:30 by andjenna          #+#    #+#             */
/*   Updated: 2024/12/02 17:24:47 by andjenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
#define PHILO_BONUS_H

#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <pthread.h>
#include <semaphore.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>

#define PURPLE "\033[0;35m"
#define YELLOW "\033[0;33m"
#define RESET "\033[0m"

typedef struct s_philo
{
	pid_t pid;
	int id;
	int last_meal;
	int nb_eaten;
	int	death;
	struct s_prog *prog;
} t_philo;

typedef struct s_prog
{
	int nb_of_philo;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int nb_time_to_eat;
	int start;
	int nb_has_eaten;
	int death_flag;
	sem_t *forks;
	sem_t *print;
	sem_t *death;
	// sem_t *has_eaten;
	t_philo *philo;
} t_prog;

/*		PARSING		*/
long ft_atol(char *str);
int is_digit(char *str);
int ft_check_params(char **av);
int ft_parse_params(int ac, char **av);

/*		INIT_STRUCT		*/
int ft_init_prog(t_prog *prog, int ac, char **av);
int ft_init_philo(t_philo *philo, t_prog *prog);

/*		UTILS		*/
int get_time_ms(void);
void ft_usleep(int time, t_philo *philo);
void ft_print_msg(t_philo *philo, char *msg);

/*		PHILO		*/
void ft_routine(t_philo *philo);


void ft_free(t_prog *prog, t_philo *philo);

void terminate_process(t_prog *prog);
int ft_check_death(t_philo *philo);
void ft_clean_sem(t_prog *prog);
int ft_check_nb_eaten(t_philo *philo);
// long				get_long_value(long *value, sem_t *sem);
// void				set_long_value(long *value, long new_value, sem_t *sem);
#endif