/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo2.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thole <thole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 17:55:12 by thole             #+#    #+#             */
/*   Updated: 2024/03/07 17:55:13 by thole            ###   ########.fr       */
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

# define ERR_NB -4
# define ERR_PARS -3
# define ERR_MALLOC -2
# define ERR_ARG -1
# define SUCCESS 777
# define ERR_THREAD -5
# define ERR_THREAD_JOIN -6
# define RED "\033[1;31m"
# define RESET "\033[0m"
# define PURP "\033[1;95m"
# define PURP2 "\033[1;35m"
# define ORANGE "\033[1;91m"
# define LIGHTB "\033[1;36m"
# define BLUE "\033[1;94m"
# define GREEN "\033[1;92m"
# define YELLOW "\033[1;93m"

typedef struct s_philo
{
	int				nb_philo;
	int				id;
	int				eating;
	int				meals_eaten;
	size_t			last_meal;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	int				nb_must_eat;
	int				*dead;
	pthread_t		thread;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*meal_lock;
	pthread_mutex_t	*dead_lock;
	int				*all_eaten;
	pthread_mutex_t	*all_eaten_lock;
}					t_philo;

typedef struct s_threads
{
	int				dead_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	int				nb_philo;
	int				all_eaten;
	pthread_mutex_t	all_eaten_lock;
}					t_threads;

int					ft_isdigit(int c);
int					ft_atoi(const char *nptr);
int					ft_strlen(char *str);
int					load_struct_no_eat(t_philo *phi, char **argv);
int					load_struct_eat(t_philo *phi, char **argv);
void				print_struct(t_philo *phi);
int					atoi_flag(char *s, int *flag);
int					is_whitespaces(int c);
int					ft_usleep(size_t milliseconds, t_philo *philo);
size_t				get_current_time(void);
int					free_all(t_threads *thread, int err);
int					init_threads(t_threads *thread);
void				*ft_checker(void *philos);
void				print_message(t_philo *philo, char *message, int philo_id);
int					init_philosophy(t_philo *phi, t_threads *thread);
int					is_dead(t_philo *philo);
void				set_death(t_philo *philo);
int					init_philo_alone(t_threads *thread);

#endif
