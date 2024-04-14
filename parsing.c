/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thole <thole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 18:45:42 by thole             #+#    #+#             */
/*   Updated: 2024/03/07 18:45:44 by thole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_is_all_num(char *s, int *flag)
{
	int	i;

	i = 0;
	while (is_whitespaces(s[i]))
		i++;
	if (s[i] == '-' || s[i] == '+')
		i++;
	while (ft_isdigit(s[i]))
		i++;
	if (s[i] && !ft_isdigit(s[i]))
		(*flag) = 1;
}

int	check_error_args(char **argv)
{
	int	i;
	int	flag;

	i = 1;
	while (argv[i])
	{
		flag = 0;
		atoi_flag(argv[i], &flag);
		check_is_all_num(argv[i], &flag);
		if (flag == 1)
			return (ERR_PARS);
		else if (atoi_flag(argv[i], &flag) <= 0)
			return (ERR_NB);
		i++;
	}
	return (SUCCESS);
}

int	load_struct_no_eat(t_philo *phi, char **argv)
{
	int	i;

	i = check_error_args(argv);
	if (i != SUCCESS)
		return (i);
	phi->nb_philo = ft_atoi(argv[1]);
	phi->time_to_die = ft_atoi(argv[2]);
	phi->time_to_eat = ft_atoi(argv[3]);
	phi->time_to_sleep = ft_atoi(argv[4]);
	phi->nb_must_eat = -1;
	if (phi->nb_philo > 200 || phi->time_to_die <= 0 || phi->time_to_eat <= 0
		|| phi->time_to_sleep <= 0 || phi->nb_philo <= 0)
		return (ERR_NB);
	return (SUCCESS);
}

int	load_struct_eat(t_philo *phi, char **argv)
{
	int	i;

	i = check_error_args(argv);
	if (i != SUCCESS)
		return (i);
	phi->nb_philo = ft_atoi(argv[1]);
	phi->time_to_die = ft_atoi(argv[2]);
	phi->time_to_eat = ft_atoi(argv[3]);
	phi->time_to_sleep = ft_atoi(argv[4]);
	phi->nb_must_eat = ft_atoi(argv[5]);
	if (phi->nb_philo > 200 || phi->nb_must_eat <= 0 || phi->time_to_die <= 0
		|| phi->time_to_eat <= 0 || phi->time_to_sleep <= 0
		|| phi->nb_philo <= 0)
		return (ERR_NB);
	return (SUCCESS);
}

void	print_struct(t_philo *phi)
{
	printf("Nb philos: %d\n", phi->nb_philo);
	printf("Time to die: %zu\n", phi->time_to_die);
	printf("Time to eat: %zu\n", phi->time_to_eat);
	printf("Time to sleep: %zu\n", phi->time_to_sleep);
	printf("How many times the should eat: %d\n", phi->nb_must_eat);
}
