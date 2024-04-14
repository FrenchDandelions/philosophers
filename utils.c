/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thole <thole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 17:48:47 by thole             #+#    #+#             */
/*   Updated: 2024/03/07 17:48:49 by thole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	atoi_len_sign(char c, int *len, int *i)
{
	if (c == '-' || c == '+')
	{
		if (c == '-')
			(*len)++;
		(*i)++;
	}
}

int	atoi_len(char *s)
{
	int	i;
	int	result;
	int	len;

	len = 0;
	i = 0;
	result = 0;
	while ((s[i] >= 9 && s[i] <= 13) || s[i] == 32)
		i++;
	atoi_len_sign(s[i], &len, &i);
	while (s[i] >= '0' && s[i] <= '9')
	{
		result = result * 10 + (s[i] - 48);
		if (result != 0)
			len++;
		i++;
	}
	return (len);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	result;
	int	sign;

	i = 0;
	sign = 1;
	result = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + (nptr[i] - 48);
		i++;
	}
	return (result * sign);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
