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

static void	eat_odd(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	print_message(philo, "\033[1;93mhas taken a fork\033[0m", philo->id);
	pthread_mutex_lock(philo->r_fork);
	print_message(philo, "\033[1;93mhas taken a fork\033[0m", philo->id);
	philo->eating = 1;
	pthread_mutex_lock(philo->meal_lock);
	print_message(philo, "\033[1;91mis eating\033[0m", philo->id);
	philo->last_meal = get_current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	ft_usleep(philo->time_to_eat, philo);
	philo->eating = 0;
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

static void	eat_even(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	print_message(philo, "\033[1;93mhas taken a fork\033[0m", philo->id);
	pthread_mutex_lock(philo->l_fork);
	print_message(philo, "\033[1;93mhas taken a fork\033[0m", philo->id);
	philo->eating = 1;
	pthread_mutex_lock(philo->meal_lock);
	print_message(philo, "\033[1;91mis eating\033[0m", philo->id);
	philo->last_meal = get_current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	ft_usleep(philo->time_to_eat, philo);
	philo->eating = 0;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	*ft_routine(void *phi)
{
	t_philo	*philo;

	philo = (t_philo *)phi;
	while (!is_dead(philo))
	{
		if (philo->id % 2 == 0)
			eat_even(philo);
		else
			eat_odd(philo);
		print_message(philo, "\033[1;94mis sleeping\033[0m", philo->id);
		ft_usleep(philo->time_to_sleep, philo);
		print_message(philo, "\033[1;92mis thinking\033[0m", philo->id);
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
		return (free_all(thread, ERR_THREAD_JOIN));
	while (i < thread->nb_philo)
	{
		if (pthread_join(thread->philos[i].thread, NULL))
			return (free_all(thread, ERR_THREAD_JOIN));
		i++;
	}
	if (thread->all_eaten)
		printf("[ All the philos finished eating! ]\n");
	return (free_all(thread, SUCCESS));
}
