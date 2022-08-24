/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equesnel <equesnel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 02:39:49 by equesnel          #+#    #+#             */
/*   Updated: 2022/08/24 22:06:38 by equesnel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"
#include <limits.h>

static int	strlen_overflow(const char *str)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] == '0')
		i++;
	while (str[i])
	{
		len++;
		i++;
	}
	return (len);
}

int	ft_atoi(const char *nptr, t_data *all)
{
	long int	result;
	int			neg;
	int			i;

	i = 0;
	result = 0;
	neg = 1;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	while (nptr[i] == '-' || nptr[i] == '+')
		if (nptr[i++] == '-')
			neg = -1;
	result = 0;
	while (nptr[i] >= '0' && nptr[i] <= '9')
		result = (nptr[i++] - 48) + (result * 10);
	if (result * neg < INT_MIN || result * neg > INT_MAX
		|| strlen_overflow(nptr) > 10)
		all->error = -1;
	return (result * neg);
}

long int	timestamp(struct timeval start)
{
	long int		s;
	long int		ms;
	struct timeval	end;

	gettimeofday(&end, NULL);
	s = (end.tv_sec - start.tv_sec) * 1000;
	ms = (end.tv_usec - start.tv_usec) / 1000;
	return (s + ms);
}

void	print_message(t_data *all, char *str, int nb)
{
	pthread_mutex_lock(&all->lock_write);
	if (!all->print)
		printf("%ld %d %s\n", timestamp(all->start), nb, str);
	pthread_mutex_unlock(&all->lock_write);
}

void	best_sleep(long int time, t_data *all)
{
	long int	begin;

	begin = timestamp(all->start);
	while (time > (timestamp(all->start) - begin))
	{
		pthread_mutex_lock(&all->lock_death);
		if (all->dead)
		{
			pthread_mutex_unlock(&all->lock_death);
			break ;
		}
		pthread_mutex_unlock(&all->lock_death);
		usleep(50);
	}
}
