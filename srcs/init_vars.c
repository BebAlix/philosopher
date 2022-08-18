/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equesnel <equesnel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 17:16:06 by equesnel          #+#    #+#             */
/*   Updated: 2022/08/18 17:04:24 by equesnel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	init_all(t_data *all, int ac, char **av)
{
	all->nb_max_philo = ft_atoi(av[1]);
	all->ttdie = ft_atoi(av[2]);
	all->tteat = ft_atoi(av[3]);
	all->ttsleep = ft_atoi(av[4]);
	if (ac == 6)
		all->eat_enought = ft_atoi(av[5]);
	else
		all->eat_enought = -1;
	all->philo = malloc(sizeof(t_philo) * all->nb_max_philo);
	all->has_eatting = malloc(sizeof(struct timeval) * all->nb_max_philo);
	all->dead = 0;
}

static void	init_philo(t_data *all)
{
	int	i;

	pthread_mutex_init(&all->lock_start, NULL);
	pthread_mutex_init(&all->lock_died, NULL);
	pthread_mutex_init(&all->lock_has_eatting, NULL);
	pthread_mutex_lock(&all->lock_start);
	i = 0;
	while (i != all->nb_max_philo)
	{
		all->philo[i].all = all;
		all->philo[i].min_eat = 0;
		all->philo[i].nb = i + 1;
		pthread_mutex_init(&all->philo[i].fork, NULL);
		pthread_create(&all->philo[i].thread, NULL, &dinner,
			&all->philo[i]);
		i++;
	}
}

void	init_vars(t_data *all, int ac, char **av)
{
	init_all(all, ac, av);
	init_philo(all);
}
