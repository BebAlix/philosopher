/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equesnel <equesnel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 00:10:21 by equesnel          #+#    #+#             */
/*   Updated: 2022/08/18 02:01:13 by equesnel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	check_digit(int ac, char **av)
{
	int	i;
	int	x;

	i = 1;
	while (i != ac)
	{
		x = 0;
		while (av[i][x])
		{
			if (av[i][x] < '0' || av[i][x] > '9')
			{
				write(2, "Wrong arguments\n", 17);
				return (-1);
			}
			x++;
		}
		i++;
	}
	return (0);
}

int	check_errors(int ac, char **av)
{
	if (ac < 5 || ac > 6)
	{
		write(2, "Wrong number of arguments\n", 27);
		return (-1);
	}
	if (check_digit(ac, av))
		return (-1);
	return (0);
}
