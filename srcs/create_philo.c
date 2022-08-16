/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equesnel <equesnel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 21:28:03 by equesnel          #+#    #+#             */
/*   Updated: 2022/08/16 13:27:43 by equesnel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/*int	give_time()
{

}*/

/*float time_diff(struct timeval *start, struct timeval *end)
{
	return (end->tv_sec - start->tv_sec) + 1e-6*(end->tv_usec - start->tv_usec);
}*/
/*
	struct timeval start;
	struct timeval end;
	gettimeofday(&start, NULL);
	loopFunc(NUM);
	gettimeofday(&end, NULL);


	int	time_to_sleep = 10;
	int	time_to_die = 5;

	gettimeofday(&start, NULL);
	usleep(time_to_sleep * 1000);
	gettimeofday(&end, NULL);
	if ((end - start) > time_to_die)
		kill_philo();

*/

int	split_sleep(int time)
{
	int	i;

	i = 0;
	while (i != time)
	{
		usleep(1000);
		i++;
	}
	return (i);
}

void	print_message(char	*str, int nb)
{
	struct timeval	timestamp;

	gettimeofday(&timestamp, NULL);
	printf("%ld%.0f %d %s\n", timestamp.tv_sec,
		(1e-3 * timestamp.tv_usec), nb, str);
}
void	lock_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	print_message("has taken a fork", philo->nb);
	if (philo->nb == philo->all->nb_max_philo)
		pthread_mutex_lock(&philo->all->philo[0].fork);
	else
		pthread_mutex_lock(&philo->all->philo[philo->nb + 1].fork);
	print_message("has taken a fork", philo->nb);
}

void	eating(t_philo *philo)
{
	print_message("is eating", philo->nb);
	usleep(philo->all->to_eat * 1000);
}

void	unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->fork);
	if (philo->nb == philo->all->nb_max_philo)
		pthread_mutex_unlock(&philo->all->philo[0].fork);
	else
		pthread_mutex_unlock(&philo->all->philo[philo->nb + 1].fork);
}

void	spleeping(t_philo *philo)
{
	print_message("is sleeping", philo->nb);
	philo->d_sword += split_sleep(philo->all->to_sleep);
	print_message("is thinking", philo->nb);
}

void	*dinner(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	usleep(100);
	lock_forks(philo);
	eating(philo);
	unlock_forks(philo);
	spleeping(philo);
	return (NULL);
}

void	create_philo(t_data *all)
{
	pthread_mutex_init(&all->lock, NULL);
	all->i = 0;
	while (all->i != all->nb_max_philo)
	{
		pthread_mutex_init(&all->philo[all->i].fork, NULL);
		all->philo[all->i].all = all;
		all->i++;
	}
	all->i = 0;
	while (all->i != all->nb_max_philo)
	{
		pthread_create(&all->philo[all->i].thread, NULL, &dinner, &all->philo[all->i]);
		pthread_mutex_lock(&all->lock);
		all->philo[all->i].nb = all->i + 1;
		all->i++;
		pthread_mutex_unlock(&all->lock);
	}
	all->i = 0;
	while (all->i != all->nb_max_philo)
	{
		pthread_join(all->philo[all->i].thread, NULL);
		all->i++;
	}
	all->i = 0;
	while (all->i != all->nb_max_philo)
	{
		pthread_mutex_destroy(&all->philo[all->i].fork);
		all->i++;
	}
	pthread_mutex_destroy(&all->lock);
}