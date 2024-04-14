/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thole <thole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 17:35:32 by thole             #+#    #+#             */
/*   Updated: 2024/03/07 17:35:34 by thole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_error(t_philo *phi, int status)
{
	(void)phi;
	if (status == ERR_ARG)
		return (printf("Error\nWrong args passsed as parameters\n"), 1);
	else if (status == ERR_PARS)
		return (printf("Error\nFound something else than numbers\n"), 1);
	else if (status == ERR_NB)
		return (printf("Error\nToo many philos or negative numbers found\n"),
			1);
	else if (status == ERR_MALLOC)
		return (printf("Error\nMalloc\n"), -2);
	return (1);
}

int	main(int argc, char **argv)
{
	t_philo		phi;
	t_threads	thread;
	int			status;

	status = SUCCESS;
	if (argc < 5 || argc > 6)
		return (print_error(&phi, ERR_ARG));
	if (argc == 5)
		status = load_struct_no_eat(&phi, argv);
	else if (argc == 6)
		status = load_struct_eat(&phi, argv);
	if (status != SUCCESS)
		return (print_error(&phi, status));
	status = init_philosophy(&phi, &thread);
	if (status != SUCCESS)
		return (status);
	return (0);
}
