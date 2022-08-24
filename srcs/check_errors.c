/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equesnel <equesnel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 00:10:21 by equesnel          #+#    #+#             */
/*   Updated: 2022/08/24 22:05:11 by equesnel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	check_digit(t_data *all, int ac, char **av)
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
				all->error = 1;
				return ;
			}
			x++;
		}
		i++;
	}
	i = 1;
}

void	check_errors(t_data *all, int ac, char **av)
{
	int	i;

	all->error = 0;
	if (ac < 5 || ac > 6)
	{
		write(2, "Wrong number of arguments\n", 27);
		all->error = 1;
		return ;
	}
	check_digit(all, ac, av);
	i = 1;
	while (i != ac)
	{
		ft_atoi(av[i], all);
		i++;
	}
	if (all->error == -1)
	{
		write(2, "int overflow !!!\n", 18);
		return ;
	}
	return ;
}
