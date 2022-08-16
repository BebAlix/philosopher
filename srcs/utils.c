/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equesnel <equesnel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 17:25:48 by equesnel          #+#    #+#             */
/*   Updated: 2022/08/15 19:37:50 by equesnel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	result;
	int	c;

	i = 0;
	result = 0;
	c = 1;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	while (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			c = -1;
		result++;
		if (result > 1)
			return (0);
		i++;
	}
	result = 0;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = (nptr[i] - 48) + (result * 10);
		i++;
	}
	return (result * c);
}

void	free_vars(t_data *all)
{
	free(all->philo);
}

void	ft_error(t_data *all)
{
	free_vars(all);
	write(2, "Error\n", 6);
	exit(0);
}
