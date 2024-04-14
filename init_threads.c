/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thole <thole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 18:19:13 by thole             #+#    #+#             */
/*   Updated: 2024/04/12 18:19:14 by thole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead == 1)
		return (pthread_mutex_unlock(philo->dead_lock), 1);
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

void	set_death(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	*philo->dead = 1;
	pthread_mutex_unlock(philo->dead_lock);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	print_message(philo, "has taken his right fork", philo->id);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_lock(philo->l_fork);
	print_message(philo, "has taken his left fork", philo->id);
	philo->eating = 1;
	pthread_mutex_lock(philo->meal_lock);
	print_message(philo, "is eating", philo->id);
	philo->last_meal = get_current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	ft_usleep(philo->time_to_eat);
	philo->eating = 0;
	pthread_mutex_unlock(philo->l_fork);
}

void	*ft_routine(void *phi)
{
	t_philo	*philo;

	philo = (t_philo *)phi;
	if (philo->id % 2 == 0)
		ft_usleep(50);
	while (!is_dead(philo))
	{
		eat(philo);
		print_message(philo, "is sleeping", philo->id);
		ft_usleep(philo->time_to_sleep);
		print_message(philo, "is thinking", philo->id);
	}
	return (phi);
}

int	init_threads(t_threads *thread)
{
	pthread_t	checker;
	int			i;

	if (pthread_create(&checker, NULL, ft_checker, thread->philos))
		return (free_all(thread, ERR_THREAD));
	i = 0;
	while (i < thread->nb_philo)
	{
		if (pthread_create(&thread->philos[i].thread, NULL, ft_routine,
				&thread->philos[i]))
			return (free_all(thread, ERR_THREAD));
		i++;
	}
	i = 0;
	if (pthread_join(checker, NULL))
		return (free_all(thread, ERR_THREAD));
	while (i < thread->nb_philo)
	{
		if (pthread_join(thread->philos[i].thread, NULL))
			return (free_all(thread, ERR_THREAD));
		i++;
	}
	if (thread->all_eaten)
		printf("[ All the philos finished eating! ]\n");
	return (free_all(thread, SUCCESS));
}
