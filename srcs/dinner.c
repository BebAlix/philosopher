/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equesnel <equesnel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 16:13:42 by equesnel          #+#    #+#             */
/*   Updated: 2022/08/18 17:04:42 by equesnel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	lock_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	print_message(philo->all, "has taken a lfork", philo->nb);
	if (philo->nb != philo->all->nb_max_philo)
		pthread_mutex_lock(&philo->all->philo[philo->nb].fork);
	else
		pthread_mutex_lock(&philo->all->philo[0].fork);
	print_message(philo->all, "has taken a rfork", philo->nb);
}

static void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->all->lock_has_eatting);
	gettimeofday(&philo->all->has_eatting[philo->nb - 1], NULL);
	pthread_mutex_unlock(&philo->all->lock_has_eatting);

	print_message(philo->all, "is eating", philo->nb);
	usleep(philo->all->tteat * 1000);
	/*if (philo->min_eat != -1)
		philo->min_eat++;*/
}

static void	unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->fork);
	if (philo->nb != philo->all->nb_max_philo)
		pthread_mutex_unlock(&philo->all->philo[(philo->nb)].fork);
	else
		pthread_mutex_unlock(&philo->all->philo[0].fork);
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
	if (philo->all->nb_max_philo % 2 != 0)
		usleep(500);
	while (1)
	{
		pthread_mutex_lock(&philo->all->lock_died);
		if (philo->all->dead == 1 || philo->min_eat == philo->all->eat_enought)
		{
			pthread_mutex_unlock(&philo->all->lock_died);
			break ;
		}
		pthread_mutex_unlock(&philo->all->lock_died);
		lock_forks(philo);
		eating(philo);
		unlock_forks(philo);
		spleep_and_think(philo);
	}
	return (NULL);
}
