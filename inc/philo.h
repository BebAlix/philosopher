/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equesnel <equesnel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 19:22:57 by equesnel          #+#    #+#             */
/*   Updated: 2022/08/16 13:41:20 by equesnel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

struct s_data;

typedef struct  s_philo
{
	pthread_mutex_t fork;
	pthread_t       thread;
	struct s_data	*all;
	int				finish_eat;
	int				nb;

}               t_philo;

typedef struct	s_data
{
	pthread_mutex_t lock;
	t_philo	*philo;
	int	nb_max_philo;
	int	to_die;
	int	to_eat;
	int	to_sleep;
	int	min_eat;
	int	i;
}				t_data;

int		check_errors(t_data *all, int ac, char **av);

void    init_vars(t_data *all, int ac, char **av);
void	create_philo(t_data *all);

/*utils*/

int		ft_atoi(const char *nptr);
void	ft_error(t_data *all);
void	free_vars(t_data *all);

// mettre un mutex pour le droit a l'ecriture sur le terminale
// mutex pour checker si ils sont mort

# endif
