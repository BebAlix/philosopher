/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equesnel <equesnel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 19:22:57 by equesnel          #+#    #+#             */
/*   Updated: 2022/08/18 17:03:38 by equesnel         ###   ########.fr       */
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
	int				nb;
	int				min_eat;

}               t_philo;

typedef struct	s_data
{
	struct timeval *has_eatting;
	struct timeval start;

	pthread_mutex_t lock_start;
	pthread_mutex_t lock_has_eatting;
	pthread_mutex_t lock_died;
	
	t_philo	*philo;
	int	nb_max_philo;
	int	ttdie;
	int	tteat;
	int	ttsleep;
	int	eat_enought;
	int	dead;
}				t_data;

int			check_errors(int ac, char **av);
void   		init_vars(t_data *all, int ac, char **av);
void		launch_thread(t_data *all);
void		*dinner(void *arg);
void		free_vars(t_data *all);

/*utils*/
int			ft_atoi(const char *nptr);
void		print_message(t_data *all, char *str, int nb);
long int	time_diff(struct timeval *start, struct timeval *end);

# endif
