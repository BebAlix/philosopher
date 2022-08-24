/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equesnel <equesnel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 17:16:06 by equesnel          #+#    #+#             */
/*   Updated: 2022/08/24 21:50:52 by equesnel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	init_all(t_data *all, int ac, char **av)
{
	int	i;

	all->nb_max_philo = ft_atoi(av[1], all);
	all->ttdie = ft_atoi(av[2], all);
	all->tteat = ft_atoi(av[3], all);
	all->ttsleep = ft_atoi(av[4], all);
	if (ac == 6)
		all->last_eat = ft_atoi(av[5], all);
	else
		all->last_eat = -1;
	all->print = 0;
	all->dead = 0;
	pthread_mutex_init(&all->lock_write, NULL);
	pthread_mutex_init(&all->lock_eat_enought, NULL);
	pthread_mutex_init(&all->lock_has_eating, NULL);
	pthread_mutex_init(&all->lock_death, NULL);
	i = 0;
	while (i != all->nb_max_philo)
	{
		pthread_mutex_init(&all->fork[i], NULL);
		i++;
	}
}

static void	init_philo(t_data *all)
{
	int	i;

	i = 0;
	while (i != all->nb_max_philo)
	{
		all->philo[i].all = all;
		all->philo[i].nb = i + 1;
		all->philo[i].lfork = i;
		all->philo[i].eat_enought = all->last_eat;
		if (all->philo[i].nb == all->nb_max_philo)
			all->philo[i].rfork = 0;
		else
			all->philo[i].rfork = i + 1;
		i++;
	}
}

void	init_vars(t_data *all, int ac, char **av)
{
	init_all(all, ac, av);
	init_philo(all);
	all->last_eat = all->nb_max_philo;
}
