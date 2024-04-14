/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thole <thole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 18:07:58 by thole             #+#    #+#             */
/*   Updated: 2024/04/12 18:07:59 by thole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_memdel(void *ptr)
{
	if (ptr)
		free(ptr);
	ptr = NULL;
}

int	free_all(t_threads *thread, int err)
{
	int	i;

	i = 0;
	while (i < thread->nb_philo)
	{
		pthread_mutex_destroy(&thread->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&thread->dead_lock);
	pthread_mutex_destroy(&thread->meal_lock);
	pthread_mutex_destroy(&thread->write_lock);
	ft_memdel(thread->philos);
	ft_memdel(thread->forks);
	return (err);
}
