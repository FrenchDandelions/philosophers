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
		return (printf("%sError\nWrong args passsed as parameters\n%s", RED,
				RESET), 2);
	else if (status == ERR_PARS)
		return (printf("%sError\nFound something else than numbers\n%s", RED,
				RESET), 2);
	else if (status == ERR_NB)
		return (printf("%sError\nToo many philos or negative numbers found\n%s",
				RED, RESET), 2);
	else if (status == ERR_MALLOC)
		return (printf("%sError\nMalloc\n%s", RED, RESET), -2);
	else if (status == ERR_THREAD)
		return (printf("%sError\nThread creation failed\n%s", RED, RESET), -2);
	else if (status == ERR_THREAD_JOIN)
		return (printf("%sError\nThread join failed\n%s", RED, RESET), -2);
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
		return (print_error(&phi, status));
	return (0);
}
