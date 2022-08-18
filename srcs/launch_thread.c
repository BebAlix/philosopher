/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equesnel <equesnel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 21:28:03 by equesnel          #+#    #+#             */
/*   Updated: 2022/08/19 00:35:52 by equesnel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/*static void	start_count(t_data *all)
{

}*/

/*static void	check_if_die(t_data *all)
{

}*/

/*static void check_finish_eat(t_data *all)
{

}*/

void	launch_thread(t_data *all)
{
	int	i;

	i = 0;
	gettimeofday(&all->start, NULL);
	pthread_mutex_unlock(&all->lock_start);
	while (i != all->nb_max_philo)
	{
		pthread_join(all->philo[i].thread, NULL);
		i++;
	}
}
