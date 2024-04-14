/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thole <thole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 16:41:48 by thole             #+#    #+#             */
/*   Updated: 2024/04/12 16:41:49 by thole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_mutex(t_threads *thread, pthread_mutex_t *forks,
		t_philo *philo, int nb_philo)
{
	thread->dead_flag = 0;
	thread->all_eaten = 0;
	thread->forks = forks;
	thread->philos = philo;
	thread->nb_philo = nb_philo;
	pthread_mutex_init(&thread->dead_lock, NULL);
	pthread_mutex_init(&thread->meal_lock, NULL);
	pthread_mutex_init(&thread->write_lock, NULL);
	pthread_mutex_init(&thread->all_eaten_lock, NULL);
}

static void	init_forks(pthread_mutex_t *forks, int nb_philo)
{
	int	i;

	i = 0;
	while (i < nb_philo)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

static void	get_info(t_philo *phi, t_philo *philo, t_threads *thread, int i)
{
	philo[i].nb_philo = phi->nb_philo;
	philo[i].time_to_die = phi->time_to_die;
	philo[i].time_to_eat = phi->time_to_eat;
	philo[i].time_to_sleep = phi->time_to_sleep;
	philo[i].nb_must_eat = phi->nb_must_eat;
	philo[i].last_meal = get_current_time();
	philo[i].start_time = get_current_time();
	philo[i].dead_lock = &thread->dead_lock;
	philo[i].meal_lock = &thread->meal_lock;
	philo[i].write_lock = &thread->write_lock;
	philo[i].all_eaten_lock = &thread->all_eaten_lock;
	philo[i].all_eaten = &thread->all_eaten;
}

static void	init_get_struct(t_philo *phi, t_philo *philo, t_threads *thread)
{
	int	i;

	i = 0;
	while (i < phi->nb_philo)
	{
		get_info(phi, philo, thread, i);
		philo[i].id = i + 1;
		philo[i].eating = 0;
		philo[i].meals_eaten = 0;
		philo[i].dead = &thread->dead_flag;
		philo[i].l_fork = &thread->forks[i];
		if (i == 0)
			philo[i].r_fork = &thread->forks[phi->nb_philo - 1];
		else
			philo[i].r_fork = &thread->forks[i - 1];
		i++;
	}
}

int	init_philosophy(t_philo *phi, t_threads *thread)
{
	t_philo			*philo;
	pthread_mutex_t	*forks;

	philo = malloc(sizeof(t_philo) * (phi->nb_philo));
	if (philo == NULL)
		return (ERR_MALLOC);
	forks = malloc(sizeof(pthread_mutex_t) * (phi->nb_philo));
	if (forks == NULL)
		return (free(philo), ERR_MALLOC);
	init_mutex(thread, forks, philo, phi->nb_philo);
	init_forks(forks, phi->nb_philo);
	init_get_struct(phi, philo, thread);
	if (thread->nb_philo == 1)
		return (init_philo_alone(thread));
	return (init_threads(thread));
}
