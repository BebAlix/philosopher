/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equesnel <equesnel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 16:54:03 by equesnel          #+#    #+#             */
/*   Updated: 2022/08/24 21:40:10 by equesnel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	main(int ac, char **av)
{
	t_data	all;

	check_errors(&all, ac, av);
	if (all.error)
		return (0);
	init_vars(&all, ac, av);
	launch_thread(&all);
	free_vars(&all);
	return (0);
}
