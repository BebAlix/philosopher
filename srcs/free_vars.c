/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_vars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equesnel <equesnel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 17:17:18 by equesnel          #+#    #+#             */
/*   Updated: 2022/08/18 17:04:23 by equesnel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	free_vars(t_data *all)
{
	int	i;

	i = 0;
	while (i != all->nb_max_philo)
	{
		pthread_mutex_destroy(&all->philo[i].fork);
		i++;
	}
	pthread_mutex_destroy(&all->lock_start);
	pthread_mutex_destroy(&all->lock_died);
	pthread_mutex_destroy(&all->lock_has_eatting);
	free(all->philo);
	free(all->has_eatting);
}
