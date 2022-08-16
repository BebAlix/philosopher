/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equesnel <equesnel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 17:16:06 by equesnel          #+#    #+#             */
/*   Updated: 2022/08/16 14:22:55 by equesnel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void    init_vars(t_data *all, int ac, char **av)
{
    all->nb_max_philo = ft_atoi(av[1]);
    all->to_die = ft_atoi(av[2]);
    all->to_eat = ft_atoi(av[3]);
    all->to_sleep = ft_atoi(av[4]);
    if (ac == 6)
        all->min_eat = ft_atoi(av[5]);
    all->philo = malloc(sizeof(t_philo) * all->nb_max_philo);
}
