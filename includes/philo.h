/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rania <rania@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 17:40:14 by rania             #+#    #+#             */
/*   Updated: 2023/02/07 15:18:25 by rania            ###   ########.fr       */
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

typedef struct s_philo t_philo;

typedef struct s_stack
{
	int				nb_philo;
	time_t			time_die;
	time_t			time_eat;
	time_t			time_sleep;
	int				nb_meal;
	time_t 			start_time;
	int				died;
	t_philo			**philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
}	t_stack;

typedef struct s_philo
{
	int			id;
	int			forks[2];
	pthread_t	thread;
	t_stack		*table;
	time_t		last_eat;
	int			died;
}	t_philo;

int		ft_check_arg(char **av);
int		ft_isdigit(int c);
int		ft_atoi(const char *nptr);
size_t	ft_strlen(const char *str);
void	ft_putnbr(long long int nbr);

#endif
