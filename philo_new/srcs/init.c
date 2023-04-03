/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamsi <tamsi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 15:34:54 by rania             #+#    #+#             */
/*   Updated: 2023/02/21 21:58:04 by tamsi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static pthread_mutex_t	*ft_init_forks(t_stack *table)
{
	int	i;
	pthread_mutex_t	*forks;

	i = 0;
	forks = malloc(sizeof(pthread_mutex_t) * (table->nb_philo + 1));
	if (!forks)
		return (NULL);
	while (i < table->nb_philo)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
			return (NULL);
		i++;
	}
	return (forks);
}

static t_philo	**ft_init_philo(t_stack *table)
{
	t_philo		**philo;
	int			i;

	i = -1;
	philo = malloc(sizeof(t_philo) * table->nb_philo);
	if (!philo)
		return (0);
	while (++i < table->nb_philo)
	{
		philo[i] = malloc(sizeof(t_philo));
		if (!philo[i])
			return (0);
		philo[i]->id = i;
		philo[i]->forks[0] = i;
		philo[i]->last_eat = 0;
		philo[i]->eat_count = 0;
		if (pthread_mutex_init(&philo[i]->mutex, 0) != 0)
			return (NULL);
		philo[i]->forks[i % 2] = philo[i]->id;
		philo[i]->forks[(i + 1) % 2] = (philo[i]->id + 1) % table->nb_philo;
		philo[i]->table = table;
	}
	return (philo);
}

t_stack	*ft_fill_table(char **av, int ac)
{
	t_stack *table;
	table = malloc(sizeof(t_stack));
	if (!table)
		return (NULL);
	table->nb_philo = ft_atoi(av[1]);
	table->time_die = ft_atoi(av[2]);
	table->time_eat = ft_atoi(av[3]);
	table->time_sleep = ft_atoi(av[4]);
	table->forks = ft_init_forks(table);
	table->philo = ft_init_philo(table);
	if (pthread_mutex_init(&table->print, NULL) != 0)
		return (NULL);
	if (pthread_mutex_init(&table->mutex, 0) != 0)
		return (NULL);
	table->start_time = 0;
	pthread_mutex_lock(&table->mutex);
	table->died = 0;
	pthread_mutex_unlock(&table->mutex);
	table->nb_meal = -1;
	if(ac == 6)
		table->nb_meal = ft_atoi(av[5]);
	return (table);
}
