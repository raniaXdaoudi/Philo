/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rania <rania@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 17:40:14 by rania             #+#    #+#             */
/*   Updated: 2023/01/12 17:52:47 by rania            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

# define RED "\033[0;31m"
# define WHITE "\033[0;37m"

typedef struct s_stack
{
	int				nb_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				nb_meal;
}	t_stack;

int		ft_check_arg(char **av);
int		ft_isdigit(int c);
int		ft_atoi(const char *nptr);

#endif
