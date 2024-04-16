/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thole <thole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 16:31:44 by thole             #+#    #+#             */
/*   Updated: 2024/04/12 16:31:45 by thole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(size_t milliseconds, t_philo *philo)
{
	size_t	start;
	size_t	time_usleep;

	time_usleep = milliseconds;
	while (time_usleep > 500)
		time_usleep /= 10;
	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
	{
		if (is_dead(philo))
			break ;
		usleep(time_usleep);
	}
	return (0);
}
