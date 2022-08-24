/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equesnel <equesnel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 21:28:03 by equesnel          #+#    #+#             */
/*   Updated: 2022/08/24 22:40:13 by equesnel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	start_count(t_data *all)
{
	long int	x;
	int			i;

	i = 0;
	gettimeofday(&all->start, NULL);
	x = timestamp(all->start);
	while (i != all->nb_max_philo)
	{
		all->has_eating[i] = x;
		i++;
	}
	gettimeofday(&all->start, NULL);
}

static void	check_if_die(t_data *all)
{
	struct timeval	current_time;
	long int		time;
	long int		has_eating;
	int				i;

	while (!all->dead)
	{
		i = -1;
		gettimeofday(&current_time, NULL);
		while (++i != all->nb_max_philo)
		{
			pthread_mutex_lock(&all->lock_has_eating);
			has_eating = all->has_eating[i];
			pthread_mutex_unlock(&all->lock_has_eating);
			time = timestamp(all->start);
			if ((time - has_eating) > (all->ttdie + 10))
			{	
				pthread_mutex_lock(&all->lock_write);
				printf("%ld %d %s\n", timestamp(all->start),
					all->philo->nb, "is dead");
				all->print = 1;
				pthread_mutex_unlock(&all->lock_write);
				pthread_mutex_lock(&all->lock_death);
				all->dead = 1;
				pthread_mutex_unlock(&all->lock_death);
				return ;
			}
			usleep(50);
		}
		pthread_mutex_lock(&all->lock_eat_enought);
		if (!all->last_eat)
		{
			pthread_mutex_unlock(&all->lock_eat_enought);
			return ;
		}
		pthread_mutex_unlock(&all->lock_eat_enought);
	}
}

void	launch_thread(t_data *all)
{
	int	i;

	i = 0;
	start_count(all);
	while (i != all->nb_max_philo)
	{
		pthread_create(&all->philo[i].thread, NULL, &dinner, &all->philo[i]);
		i++;
	}
	check_if_die(all);
	i = 0;
	while (i != all->nb_max_philo)
	{
		pthread_join(all->philo[i].thread, NULL);
		i++;
	}
}
