/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamsi <tamsi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 17:40:14 by rania             #+#    #+#             */
/*   Updated: 2023/02/21 21:28:10 by tamsi            ###   ########.fr       */
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
	int				nb_meal;
	int				died;
	time_t			time_die;
	time_t			time_eat;
	time_t			time_sleep;
	time_t 			start_time;
	t_philo			**philo;
	pthread_t		death;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	mutex;
}	t_stack;

typedef struct s_philo
{
	int				id;
	int				forks[2];
	int 			eat_count;
	int				died;
	pthread_t		thread;
	pthread_mutex_t	mutex;
	t_stack			*table;
	time_t			last_eat;
}	t_philo;

void	wait_time(t_stack *table, time_t time);
void	ft_putnbr(long long int nbr);
void	*routine(void *data);
void	*routine_death(void *data);
void	ft_print(t_philo *philo, char *str);
int		get_death(t_stack *table);
int		ft_check_arg(char **av);
int		ft_isdigit(int c);
int		ft_atoi(const char *nptr);
int		is_finish(t_stack *table);
size_t	ft_strlen(const char *str);
time_t	get_current_time(void);
t_stack	*ft_fill_table(char **av, int ac);

#endif
