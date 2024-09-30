/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andjenna <andjenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 13:43:24 by andjenna          #+#    #+#             */
/*   Updated: 2024/09/26 04:42:07 by andjenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define RED		"\033[0;31m"
#define GREEN	"\033[0;32m"
#define YELLOW	"\033[0;33m"
#define BLUE	"\033[0;34m"
#define PURPLE	"\033[0;35m"
#define CYAN	"\033[0;36m"
#define RESET	"\033[0m"

// ./philosoher nb_of_philo time_to_die time_to_eat time_to_sleep [nb_of_time_each_philo_must_eat]

typedef struct s_philo
{
	pthread_t		tid;
	int				nb_time_to_eat;
	int				has_eaten;
	int				last_meal;
	int				death;
	pthread_mutex_t	*fork;

}					t_philo;

typedef struct s_prog
{
	int				nb_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	pthread_mutex_t	print;
	pthread_mutex_t	death;
	pthread_mutex_t	data_lock;
	t_philo			*philo;
}					t_prog;

/*		PARSING		*/
long				ft_atol(char *str);
int					is_digit(char *str);
int					parse_args(char **av);
int					ft_parse_params(int ac, char **av);

/*		INIT		*/
t_prog				*init_prog(char **av);
t_philo				*init_philo(char **av);
void				init_mutex(t_prog *prog);

/*		FREE		*/
void				free_prog(t_prog *prog);
void				free_philo(t_philo *philo, int i);
