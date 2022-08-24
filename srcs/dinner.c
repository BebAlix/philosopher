/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equesnel <equesnel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 16:13:42 by equesnel          #+#    #+#             */
/*   Updated: 2022/08/24 22:39:05 by equesnel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	check_eat(t_philo *philo, t_data *all)
{
	pthread_mutex_lock(&all->lock_write);
	if (!all->print)
		printf("%ld %d %s\n", timestamp(all->start),
			philo->nb, "is eating");
	if (--philo->eat_enought == 0)
	{
		pthread_mutex_lock(&all->lock_eat_enought);
		all->last_eat--;
		if (all->last_eat == 0)
			all->print = 1;
		pthread_mutex_unlock(&all->lock_eat_enought);
	}
	pthread_mutex_unlock(&all->lock_write);
	pthread_mutex_lock(&all->lock_has_eating);
	all->has_eating[philo->nb - 1] = timestamp(all->start);
	pthread_mutex_unlock(&all->lock_has_eating);
}

static void	eating(t_philo *philo, t_data *all)
{
	if (philo->nb % 2)
	{
		pthread_mutex_lock(&all->fork[philo->lfork]);
		print_message(all, "has taken a fork", philo->nb);
		pthread_mutex_lock(&all->fork[philo->rfork]);
		print_message(all, "has taken a fork", philo->nb);
	}
	else
	{
		pthread_mutex_lock(&all->fork[philo->rfork]);
		print_message(all, "has taken a fork", philo->nb);
		pthread_mutex_lock(&all->fork[philo->lfork]);
		print_message(all, "has taken a fork", philo->nb);
	}
	check_eat(philo, all);
	best_sleep(all->tteat, all);
	pthread_mutex_unlock(&all->fork[philo->lfork]);
	pthread_mutex_unlock(&all->fork[philo->rfork]);
	print_message(all, "is sleeping", philo->nb);
	best_sleep(all->ttsleep, all);
	print_message(all, "is thinking", philo->nb);
}

static int	is_solo(t_philo *philo, t_data *all)
{
	if (all->nb_max_philo == 1)
	{
		pthread_mutex_lock(&all->fork[philo->lfork]);
		print_message(all, "has taken a fork", philo->nb);
		usleep((all->ttdie + 10) * 1000);
		pthread_mutex_unlock(&all->fork[philo->lfork]);
		return (1);
	}
	return (0);
}

void	*dinner(void *arg)
{
	t_philo	*philo;
	t_data	*all;

	philo = (t_philo *)arg;
	all = philo->all;
	if (is_solo(philo, all))
		return (NULL);
	if (philo->nb % 2)
		usleep(500);
	while (philo->eat_enought)
	{
		pthread_mutex_lock(&all->lock_death);
		if (all->dead)
		{
			pthread_mutex_unlock(&all->lock_death);
			break ;
		}
		pthread_mutex_unlock(&all->lock_death);
		eating(philo, all);
	}
	return (NULL);
}
