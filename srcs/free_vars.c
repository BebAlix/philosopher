/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_vars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equesnel <equesnel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 17:17:18 by equesnel          #+#    #+#             */
/*   Updated: 2022/08/24 21:17:24 by equesnel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	free_vars(t_data *all)
{
	int	i;

	i = 0;
	while (i != all->nb_max_philo)
	{
		pthread_mutex_destroy(&all->fork[i]);
		i++;
	}
	pthread_mutex_destroy(&all->lock_write);
	pthread_mutex_destroy(&all->lock_eat_enought);
	pthread_mutex_destroy(&all->lock_has_eating);
	pthread_mutex_destroy(&all->lock_death);
}
