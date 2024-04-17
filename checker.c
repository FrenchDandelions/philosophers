/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thole <thole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 16:11:55 by thole             #+#    #+#             */
/*   Updated: 2024/04/13 16:11:56 by thole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	monitor_death_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->meal_lock);
	if (get_current_time() - philo->last_meal >= philo->time_to_die)
		return (pthread_mutex_unlock(philo->meal_lock), 1);
	pthread_mutex_unlock(philo->meal_lock);
	return (0);
}

static int	monitor_meal_checker(t_philo *philos, int must_eat)
{
	int	i;
	int	total_meals;

	total_meals = 0;
	i = 0;
	if (must_eat == -1)
		return (0);
	while (i < philos[0].nb_philo)
	{
		pthread_mutex_lock(philos[i].meal_lock);
		if (philos[i].meals_eaten >= must_eat)
			total_meals++;
		pthread_mutex_unlock(philos[i].meal_lock);
		i++;
		ft_usleep(1, &philos[i - 1]);
	}
	if (total_meals >= philos[0].nb_philo)
	{
		set_death(&philos[0]);
		pthread_mutex_lock(philos[0].all_eaten_lock);
		*philos[0].all_eaten = 1;
		pthread_mutex_unlock(philos[0].all_eaten_lock);
		return (1);
	}
	return (0);
}

static int	monitor_death_checker(t_philo *philos, int nb_philos)
{
	int	i;

	i = 0;
	while (i < nb_philos)
	{
		ft_usleep(1, &philos[i]);
		if (monitor_death_philo(&philos[i]))
		{
			print_message(&philos[i], "\033[1;31mdied\033[0m", philos[i].id);
			set_death(&philos[i]);
			return (1);
		}
		i++;
	}
	return (0);
}

void	*ft_checker(void *philos)
{
	t_philo	*phi;

	phi = (t_philo *)philos;
	while (1)
	{
		if (monitor_death_checker(phi, phi[0].nb_philo)
			|| monitor_meal_checker(phi, phi[0].nb_must_eat))
			break ;
	}
	return (philos);
}
