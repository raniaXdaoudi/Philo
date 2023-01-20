/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rania <rania@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 17:40:14 by rania             #+#    #+#             */
/*   Updated: 2023/01/20 13:51:23 by rania            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>

# define RED "\033[0;31m"
# define WHITE "\033[0;37m"

typedef struct s_stack
{
	int				nb_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				nb_meal;
	pthread_mutex_t	*forks;
}	t_stack;

typedef struct s_philo
{
	int			id;
	int			forks[2];
	pthread_t	thread;
	t_stack		*table;
}	t_philo;

int		ft_check_arg(char **av);
int		ft_isdigit(int c);
int		ft_atoi(const char *nptr);

#endif
