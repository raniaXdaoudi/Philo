/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rania <rania@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 17:43:31 by rania             #+#    #+#             */
/*   Updated: 2023/01/20 14:55:53 by rania            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t	get_current_time(void)
{
	struct timeval	tval;

	gettimeofday(&tval, NULL);
	return ((tval.tv_sec * 1000) + (tval.tv_usec / 1000));
}

pthread_mutex_t	*ft_init_forks(t_stack *table)
{
	int	i;
	pthread_mutex_t	*forks;

	i = -1;
	forks = malloc(sizeof(pthread_mutex_t) * table->nb_philo);
	if (!forks)
		return (NULL);
	while (++i < table->nb_philo)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
			return (NULL);
	}
	return (forks);
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
	if(ac == 6)
		table->nb_meal = ft_atoi(av[5]);
	return (table);
}
void *routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	pthread_mutex_lock(&philo->table->forks[philo->forks[0]]);
	printf("%lu %i has taken a fork.\n", get_current_time(), philo->id);
	pthread_mutex_lock(&philo->table->forks[philo->forks[1]]);
	printf("%lu %i has taken a fork.\n", get_current_time(), philo->id);
	printf("%lu %i is eating.\n", get_current_time(), philo->id);
	usleep(philo->table->time_eat);
	pthread_mutex_unlock(&philo->table->forks[philo->forks[0]]);
	pthread_mutex_unlock(&philo->table->forks[philo->forks[1]]);
	printf("%lu %i is sleeping.\n", get_current_time(), philo->id);
	usleep(philo->table->time_sleep);
	printf("%lu %i is thinking.\n", get_current_time(), philo->id);
	return NULL;
}

t_philo	**ft_init_philo(t_stack *table)
{
	t_philo		**philo;
	int			i;

	i = -1;
	philo = malloc(sizeof(t_philo *) * table->nb_philo);
	if (!philo)
		return (0);
	while (++i < table->nb_philo)
	{
		philo[i] = malloc(sizeof(t_philo));
		if (!philo[i])
			return (0);
		philo[i]->id = i;
		philo[i]->forks[0] = i;
		if (philo[i]->id == table->nb_philo - 1)
				philo[i]->forks[1] = 0;
		else
			philo[i]->forks[1] = i + 1;
		philo[i]->table = table;
	}
	return (philo);
}

void	ft_open_thread(t_philo **philo, t_stack *table)
{
	int	i;

	i = -1;
	while(++i < table->nb_philo)
		pthread_create(&philo[i]->thread, NULL, routine, philo[i]);
}

int main(int ac, char **av)
{
	t_stack	*table;
	t_philo	**philo;
	int		i;

	if (ac != 5 && ac != 6)
	{
		printf(RED"Bad number of args.\n"WHITE);
		return (0);
	}
	if (!ft_check_arg(av))
		return (0);
	table = ft_fill_table(av, ac);
	philo = ft_init_philo(table);
	ft_open_thread(philo, table);
	i = -1;
	while(++i < table->nb_philo)
	{
		pthread_join(philo[i]->thread, NULL);
		pthread_mutex_destroy(&table->forks[i]);
	}
	return (0);
}
