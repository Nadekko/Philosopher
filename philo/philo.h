/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andjenna <andjenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 13:43:24 by andjenna          #+#    #+#             */
/*   Updated: 2024/12/03 18:52:28 by andjenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <errno.h>

# define PURPLE "\033[0;35m"
# define YELLOW "\033[0;33m"
# define RESET "\033[0m"

typedef struct s_philo
{
	pthread_t		tid;
	int				id;
	int				nb_time_to_eat;
	int				nb_eaten;
	int				last_meal;
	pthread_mutex_t	l_fork;
	pthread_mutex_t	*r_fork;
	struct s_prog	*prog;
}					t_philo;

typedef struct s_prog
{
	int				nb_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_time_to_eat;
	int				start;
	int				has_eaten;
	int				death;
	pthread_mutex_t	print;
	pthread_mutex_t	data;
	t_philo			*philo;
}					t_prog;

/*		PARSING		*/
long				ft_atol(char *str);
int					is_digit(char *str);
int					ft_check_params(char **av);
int					ft_parse_params(int ac, char **av);

/*		INIT		*/
int					ft_init_philo(t_philo *philo, t_prog *prog);
int					ft_init_prog(t_prog *prog, int ac, char **av);

/*		UITLS		*/
void				ft_usleep(int time, t_philo *philo);
int					get_time_ms(void);
void				ft_print_msg(t_philo *philo, char *msg);
int					get_value(int *value, pthread_mutex_t *data);
void				set_value(int *value, int new_value, pthread_mutex_t *data);

/*		PHILOSOPHER		*/
int					ft_check_death(t_philo *philo);
int					ft_check_has_eaten(t_philo *philo);
int					ft_check_nb_eaten(t_philo *philo);
int					ft_check_has_eaten(t_philo *philo);
void				*ft_routine(void *args);

/*		SUPERVISOR		*/
void				*ft_supervisor_routine(void *args);

/*		FREE		*/
void				ft_free(t_prog *prog);
void				ft_error_free(t_philo *philo, int i);
void				destroy_mutex(t_prog *prog, int i);

#endif
