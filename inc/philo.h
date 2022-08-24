/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equesnel <equesnel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 19:22:57 by equesnel          #+#    #+#             */
/*   Updated: 2022/08/24 21:51:43 by equesnel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

struct	s_data;

typedef struct s_philo
{
	pthread_t		thread;
	struct s_data	*all;
	int				eat_enought;
	int				nb;
	int				lfork;
	int				rfork;
}t_philo;

typedef struct s_data
{
	struct timeval	start;

	pthread_mutex_t	lock_has_eating;
	pthread_mutex_t	lock_death;
	pthread_mutex_t	lock_eat_enought;
	pthread_mutex_t	lock_write;
	pthread_mutex_t	lock_start;

	pthread_mutex_t	fork[1000];
	t_philo			philo[1000];
	long int		has_eating[1000];
	int				nb_max_philo;
	int				ttdie;
	int				tteat;
	int				ttsleep;
	int				last_eat;
	int				print;
	int				dead;
	int				error;

}t_data;

void		check_errors(t_data *all, int ac, char **av);
void		init_vars(t_data *all, int ac, char **av);
void		launch_thread(t_data *all);
void		*dinner(void *arg);
void		free_vars(t_data *all);

/*utils*/
int			ft_atoi(const char *nptr, t_data *all);
void		best_sleep(long int time, t_data *all);
void		print_message(t_data *all, char *str, int nb);
long int	timestamp(struct timeval start);

#endif
