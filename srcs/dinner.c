/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equesnel <equesnel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 16:13:42 by equesnel          #+#    #+#             */
/*   Updated: 2022/08/18 18:53:26 by equesnel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	lock_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	print_message(philo->all, "has taken a Lfork", philo->nb);
	if (philo->nb == philo->all->nb_max_philo)
		pthread_mutex_lock(&philo->all->philo[0].fork);
	else
		pthread_mutex_lock(&philo->all->philo[philo->nb].fork);
	print_message(philo->all, "has taken a Rfork", philo->nb);
}

static void	eating(t_philo *philo)
{
	print_message(philo->all, "is eating", philo->nb);
	usleep(philo->all->tteat * 1000);
	if (philo->all->eat_enought != -1)
		philo->min_eat++;
}

static void	unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->fork);
	if (philo->nb == philo->all->nb_max_philo)
		pthread_mutex_unlock(&philo->all->philo[0].fork);
	else
		pthread_mutex_unlock(&philo->all->philo[philo->nb].fork);
}

static void	spleep_and_think(t_philo *philo)
{
	print_message(philo->all, "is sleeping", philo->nb);
	usleep(philo->all->ttsleep * 1000);
	print_message(philo->all, "is thinking", philo->nb);
}

void	*dinner(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->all->lock_start);
	pthread_mutex_unlock(&philo->all->lock_start);
	if (philo->nb % 2 != 0)
		usleep(500);
	while (1)
	{
		if (philo->min_eat == philo->all->eat_enought)
			break;
		lock_forks(philo);
		eating(philo);
		unlock_forks(philo);
		spleep_and_think(philo);
	}
	return (NULL);
}
