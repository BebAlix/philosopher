/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equesnel <equesnel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 16:54:03 by equesnel          #+#    #+#             */
/*   Updated: 2022/08/18 02:03:31 by equesnel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	main(int ac, char **av)
{
	t_data	all;

	if (check_errors(ac, av) == -1)
		return (0);
	init_vars(&all, ac, av);
	launch_thread(&all);
	free_vars(&all);
	return (0);
}
