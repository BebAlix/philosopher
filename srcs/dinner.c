/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equesnel <equesnel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 16:13:42 by equesnel          #+#    #+#             */
/*   Updated: 2022/08/19 01:38:15 by equesnel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static long long	time_diff(struct timeval *start, struct timeval *end)
{
	long long	s;
	long long	ms;

	s = (end->tv_sec - start->tv_sec) * 1000;
	ms = (end->tv_usec - start->tv_usec) / 1000;
	return (s + ms);
}

static void	print_message(t_data *all, char *str, int nb)
{
	struct timeval	end;

	pthread_mutex_lock(&all->lock_write);
	gettimeofday(&end, NULL);
	printf("%lld %d %s\n", time_diff(&all->start, &end), nb, str);
	pthread_mutex_unlock(&all->lock_write);
}

static void	philosopher(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	print_message(philo->all, "has taken a Lfork", philo->nb);
	if (philo->nb == philo->all->nb_max_philo)
		pthread_mutex_lock(&philo->all->philo[0].fork);
	else
		pthread_mutex_lock(&philo->all->philo[philo->nb].fork);
	print_message(philo->all, "has taken a Rfork", philo->nb);
	print_message(philo->all, "is eating", philo->nb);
	usleep(philo->all->tteat * 1000);
	pthread_mutex_unlock(&philo->fork);
	if (philo->nb == philo->all->nb_max_philo)
		pthread_mutex_unlock(&philo->all->philo[0].fork);
	else
		pthread_mutex_unlock(&philo->all->philo[philo->nb].fork);
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
	while (philo->min_eat != philo->all->eat_enought || philo->all->dead == 1)
	{
		philosopher(philo);
		if (philo->all->eat_enought != -1)
			philo->min_eat++;
	}
	return (NULL);
}
