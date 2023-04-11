/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radaoudi <radaoudi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 14:15:24 by rania             #+#    #+#             */
/*   Updated: 2023/04/11 17:21:20 by radaoudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	eat(t_philo *philo)
{
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

void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	pthread_mutex_lock(&philo->table->print);
	philo->last_eat = philo->table->start_time;
	pthread_mutex_unlock(&philo->table->print);
	if (philo->id % 2 == 0)
		usleep(philo->table->time_eat * 1000);
	else
		usleep(philo->table->nb_philo * 500);
	while (get_death(philo))
	{
		if (!get_death(philo))
			return (NULL);
		eat(philo);
		if (!get_death(philo))
			return (NULL);
		ft_print(philo, "is sleeping.\n");
		wait_time(philo->table, get_current_time() + philo->table->time_sleep);
		if (!get_death(philo))
			return (NULL);
		ft_print(philo, "is thinking.\n");
	}
	return (NULL);
}

int	routine_deathpt2(t_philo **philo)
{
	int	i;

	i = 0;
	while (i < philo[0]->table->nb_philo)
	{
		if (philo[i]->eat_count < philo[0]->table->nb_meal)
			philo[0]->table->check_eat_count = 0;
		if (!get_death(philo[i]))
			return (0);
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
		if (!routine_deathpt2(philo))
			return (NULL);
		if (philo[0]->table->check_eat_count == 1)
		{
			philo[0]->table->died = 1;
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}

int	get_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->print);
	if (philo->table->died == 1)
	{
		pthread_mutex_unlock(&philo->table->print);
		return (0);
	}
	else if (philo->last_eat < get_current_time() - philo->table->time_die)
	{
		printf("%lu %i died.\n", get_current_time() - philo->table->start_time, philo->id + 1);
		philo->table->died = 1;
		pthread_mutex_unlock(&philo->table->print);
		return (0);
	}
	pthread_mutex_unlock(&philo->table->print);
	return (1);
}
