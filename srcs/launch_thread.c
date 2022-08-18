/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equesnel <equesnel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 21:28:03 by equesnel          #+#    #+#             */
/*   Updated: 2022/08/18 17:05:04 by equesnel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	start_count(t_data *all)
{
	int	i;

	i = 0;
	gettimeofday(&all->start, NULL);
	while (i != all->nb_max_philo)
	{
		all->has_eatting[i] = all->start;
		i++;
	}
}

static void	check_if_die(t_data *all)
{
	struct timeval	current_time;
	int				i;

	while (1)
	{
		i = 0;
		usleep(5000);
		gettimeofday(&current_time, NULL);
		while (i != all->nb_max_philo)
		{
			pthread_mutex_lock(&all->lock_has_eatting);
			if (time_diff(&all->has_eatting[i], &current_time) >= all->ttdie)
			{
				pthread_mutex_unlock(&all->lock_has_eatting);
				print_message(all, "died", (i + 1));
				pthread_mutex_lock(&all->lock_died);
				all->dead = 1;
				pthread_mutex_unlock(&all->lock_died);
				return ;
			}
			i++;
		}
	}
}

void	launch_thread(t_data *all)
{
	int	i;

	start_count(all);
	pthread_mutex_unlock(&all->lock_start);
	check_if_die(all);
	i = 0;
	while (i != all->nb_max_philo)
	{
		pthread_join(all->philo[i].thread, NULL);
		i++;
	}
}
