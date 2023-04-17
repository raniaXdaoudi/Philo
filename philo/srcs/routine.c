/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radaoudi <radaoudi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 14:15:24 by rania             #+#    #+#             */
/*   Updated: 2023/04/17 16:06:17 by radaoudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	eat(t_philo *philo)
{
	if (!get_death(philo->table))
		return ;
	pthread_mutex_lock(&philo->table->forks[philo->forks[0]]);
	ft_print(philo, "has taken a fork.\n");
	pthread_mutex_lock(&philo->table->forks[philo->forks[1]]);
	ft_print(philo, "has taken a fork.\n");
	ft_print(philo, "is eating.\n");
	pthread_mutex_lock(&philo->mutex_philo);
	philo->last_eat = get_current_time();
	pthread_mutex_unlock(&philo->mutex_philo);
	wait_time(philo->table, get_current_time() + philo->table->time_eat);
	pthread_mutex_lock(&philo->mutex_philo);
	philo->eat_count += 1;
	pthread_mutex_unlock(&philo->mutex_philo);
	pthread_mutex_unlock(&philo->table->forks[philo->forks[0]]);
	pthread_mutex_unlock(&philo->table->forks[philo->forks[1]]);
}

static void	think(t_philo *philo)
{
	time_t	time_to_think;

	pthread_mutex_lock(&philo->mutex_philo);
	time_to_think = (philo->table->time_die
			- (get_current_time() - philo->last_eat)
			- philo->table->time_eat) / 2;
	pthread_mutex_unlock(&philo->mutex_philo);
	if (time_to_think < 0)
		time_to_think = 0;
	if (time_to_think > 600)
		time_to_think = 200;
	if (!get_death(philo->table))
		return ;
	ft_print(philo, "is thinking.\n");
	wait_time(philo->table, get_current_time() + time_to_think);
}

void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	pthread_mutex_lock(&philo->mutex_philo);
	philo->last_eat = philo->table->start_time;
	pthread_mutex_unlock(&philo->mutex_philo);
	if (philo->id % 2 == 0)
		wait_time(philo->table, philo->table->start_time
			+ philo->table->time_eat);
	else
		wait_time(philo->table, philo->table->start_time);
	while (get_death(philo->table))
	{
		eat(philo);
		if (!get_death(philo->table))
			return (NULL);
		ft_print(philo, "is sleeping.\n");
		wait_time(philo->table, get_current_time() + philo->table->time_sleep);
		if (!get_death(philo->table))
			return (NULL);
		think(philo);
	}
	return (NULL);
}

static int	cond_die(t_philo **philo)
{
	int	i;

	i = 0;
	while (i < philo[0]->table->nb_philo)
	{
		pthread_mutex_lock(&philo[i]->mutex_philo);
		if (philo[i]->last_eat < get_current_time()
			- philo[i]->table->time_die)
		{
			pthread_mutex_lock(&philo[i]->table->print);
			philo[i]->table->died = 1;
			printf("%lu %i died.\n", get_current_time()
				- philo[i]->table->start_time, philo[i]->id + 1);
			pthread_mutex_unlock(&philo[i]->table->print);
			pthread_mutex_unlock(&philo[i]->mutex_philo);
			return (0);
		}
		if (philo[i]->eat_count < philo[0]->table->nb_meal)
			philo[0]->table->check_eat_count = 0;
		pthread_mutex_unlock(&philo[i]->mutex_philo);
		i++;
	}
	return (1);
}

void	*routine_death(void *data)
{
	t_philo	**philo;

	philo = (t_philo **)data;
	usleep(philo[0]->table->time_die * 1000);
	while (1)
	{
		philo[0]->table->check_eat_count = 1;
		if (philo[0]->table->nb_meal == -1)
			philo[0]->table->check_eat_count = 0;
		if (!cond_die(philo))
			return (0);
		if (philo[0]->table->check_eat_count == 1)
		{
			pthread_mutex_lock(&philo[0]->table->print);
			philo[0]->table->died = 1;
			pthread_mutex_unlock(&philo[0]->table->print);
			return (0);
		}
		usleep(1000);
	}
	return (NULL);
}
