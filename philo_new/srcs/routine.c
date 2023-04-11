/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radaoudi <radaoudi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 14:15:24 by rania             #+#    #+#             */
/*   Updated: 2023/04/11 11:25:31 by radaoudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_finish(t_stack *table)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(&table->mutex);
	if (table->died == 1)
		ret = 1;
	pthread_mutex_unlock(&table->mutex);
	return (ret);
}

static void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->forks[philo->forks[0]]);
	ft_print(philo, "has taken a fork.\n");
	pthread_mutex_lock(&philo->table->forks[philo->forks[1]]);
	ft_print(philo, "has taken a fork.\n");
	ft_print(philo, "is eating.\n");
	philo->last_eat = get_current_time();
	wait_time(philo->table, get_current_time() + philo->table->time_eat);
	pthread_mutex_lock(&philo->mutex);
	philo->eat_count += 1;
	pthread_mutex_unlock(&philo->mutex);
	pthread_mutex_unlock(&philo->table->forks[philo->forks[0]]);
	pthread_mutex_unlock(&philo->table->forks[philo->forks[1]]);
}

void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	philo->last_eat = philo->table->start_time;
	if (philo->id % 2 == 0)
		usleep(philo->table->time_eat * 1000);
	while (!is_finish(philo->table))
	{
		if (is_finish(philo->table))
			return (NULL);
		eat(philo);
		if (!is_finish(philo->table))
		{
			ft_print(philo, "is sleeping.\n");
			wait_time(philo->table, get_current_time() + philo->table->time_sleep);
		}
		if (!is_finish(philo->table))
			ft_print(philo, "is thinking.\n");
	}
	return (NULL);
}

void	*routine_death(void *data)
{
	t_stack	*table;

	table = (t_stack *)data;
	usleep(table->time_eat * 1000);
	while (1)
	{
		if (get_death(table))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}

static void	death_part_get(t_stack *table, int i)
{

	// ft_putnbr(get_current_time() - table->start_time);
	// write(1, " ", 1);
	// ft_putnbr(table->philo[i]->id + 1);
	// write(1, " ", 1);
	// write(1, "died.\n", ft_strlen("died.\n"));
	// table->died = 1;
	// pthread_mutex_unlock(&table->print);
	// ft_print(table->philo[i], "died.\n");
	// pthread_mutex_lock(&table->mutex);
	table->died = 1;
	// pthread_mutex_unlock(&table->mutex);
	printf("%lu %i died.\n", get_current_time() - table->philo[i]->table->start_time, table->philo[i]->id + 1);
	pthread_mutex_unlock(&table->philo[i]->mutex);
}

int	get_death(t_stack *table)
{
	int	check_eat_count;
	int	i;

	i = 0;
	check_eat_count = 1;
	if (table->nb_meal == -1)
		check_eat_count = 0;
	while (i < table->nb_philo)
	{
		pthread_mutex_lock(&table->philo[i]->mutex);
		if (table->philo[i]->eat_count < table->nb_meal)
			check_eat_count = 0;
		if ((get_current_time() - table->philo[i]->last_eat)
			>= table->time_die)
		{
			death_part_get(table, i);
			return (1);
		}
		pthread_mutex_unlock(&table->philo[i]->mutex);
		i++;
	}
	pthread_mutex_lock(&table->mutex);
	table->died = check_eat_count;
	pthread_mutex_unlock(&table->mutex);
	return (check_eat_count);
}