/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_alone.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thole <thole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 15:46:21 by thole             #+#    #+#             */
/*   Updated: 2024/04/14 15:46:22 by thole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_death(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	*philo->dead = 1;
	pthread_mutex_unlock(philo->dead_lock);
}

static void	*philo_one(void *phi)
{
	t_philo	*philo;

	philo = (t_philo *)phi;
	pthread_mutex_lock(philo->r_fork);
	print_message(philo, "has taken his right fork", philo->id);
	pthread_mutex_unlock(philo->r_fork);
	ft_usleep(philo->time_to_die, philo);
	print_message(philo, "died", philo->id);
	return (phi);
}

int	init_philo_alone(t_threads *thread)
{
	if (pthread_create(&thread->philos[0].thread, NULL, philo_one,
			&thread->philos[0]))
		return (free_all(thread, ERR_THREAD));
	if (pthread_join(thread->philos[0].thread, NULL))
		return (free_all(thread, ERR_THREAD));
	return (free_all(thread, SUCCESS));
}
