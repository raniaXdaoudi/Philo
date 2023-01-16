/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rania <rania@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 17:43:31 by rania             #+#    #+#             */
/*   Updated: 2023/01/16 20:59:59 by rania            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t	get_current_time(void)
{
	struct timeval	tval;

	gettimeofday(&tval, NULL);
	return ((tval.tv_sec * 1000) + (tval.tv_usec / 1000));
}

t_stack	*ft_fill_table(char **av, int ac)
{
	t_stack *table;
	table = malloc(sizeof(t_stack));
	if(!table)
		return (NULL);
	table->nb_philo = ft_atoi(av[1]);
	table->time_die = ft_atoi(av[2]);
	table->time_eat = ft_atoi(av[3]);
	table->time_sleep = ft_atoi(av[4]);
	if(ac == 6)
		table->nb_meal = ft_atoi(av[5]);
	return (table);
}
void *routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	// pthread_mutex_lock(&forks[0]);
	// pthread_mutex_lock(&forks[1]);
	printf("%lu %i is thinking.\n", get_current_time(), philo->id);
	usleep(philo->stack->time_sleep);
	printf("%lu %i is sleeping.\n", get_current_time(), philo->id);
	// pthread_mutex_unlock(&forks[0]);
	// pthread_mutex_unlock(&forks[1]);
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
		philo[i]->id = i + 1;
		philo[i]->stack = table;
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
	// pthread_mutex_t    forks[2];
	// pthread_mutex_init(&forks[0], NULL);
	// pthread_mutex_init(&forks[1], NULL);
	while(++i < table->nb_philo)
	{
		pthread_join(philo[i]->thread, NULL);
		// pthread_mutex_destroy(&forks[i]);
	}
	return (0);
}
