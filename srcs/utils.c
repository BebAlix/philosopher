/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equesnel <equesnel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 17:25:48 by equesnel          #+#    #+#             */
/*   Updated: 2022/08/18 00:39:10 by equesnel         ###   ########.fr       */
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

long int	time_diff(struct timeval *start, struct timeval *end)
{
	int	s;
	int	ms;

	s = (end->tv_sec - start->tv_sec) * 1000;
	ms = (end->tv_usec - start->tv_usec) / 1000;
	return (s + ms);
}

void	print_message(t_data *all, char *str, int nb)
{
	struct timeval	end;
	long int		time;

	gettimeofday(&end, NULL);
	time = time_diff(&all->start, &end);
	printf("%ld %d %s\n", time, nb, str);
}
