/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_flag.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thole <thole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 17:01:39 by thole             #+#    #+#             */
/*   Updated: 2024/03/30 17:01:41 by thole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(t_philo *philo, char *message, int philo_id)
{
	size_t	current_time;

	pthread_mutex_lock(philo->write_lock);
	current_time = get_current_time() - philo->start_time;
	if (!is_dead(philo))
	{
		if (message)
			printf("[%zu] Philo %d %s\n", current_time, philo_id, message);
		else
			printf("[%zu] All Philosophers have finished eating\n",
				current_time);
	}
	pthread_mutex_unlock(philo->write_lock);
	return ;
}

int	is_whitespaces(int c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

static void	check_sign(char c, int *i, int *neg)
{
	if (c == '+' || c == '-')
	{
		if (c == '-')
			(*neg) *= -1;
		(*i)++;
	}
}

static int	check_flow(long int nb, int *flag, int neg)
{
	long int	num;

	num = nb;
	num *= -1;
	if (neg == -1 && num < INT_MIN)
	{
		(*flag) = 1;
		return (1);
	}
	else if (nb > INT_MAX)
	{
		(*flag) = 1;
		return (1);
	}
	return (0);
}

int	atoi_flag(char *s, int *flag)
{
	int			i;
	long int	nb;
	int			neg;

	i = 0;
	neg = 1;
	nb = 0;
	while (is_whitespaces(s[i]))
		i++;
	check_sign(s[i], &i, &neg);
	while (s[i] >= '0' && s[i] <= '9')
	{
		nb = nb * 10 + (s[i] - 48);
		if (check_flow(nb, flag, neg))
			return (2);
		i++;
	}
	return ((int)(nb * neg));
}
