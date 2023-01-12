/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rania <rania@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 17:43:31 by rania             #+#    #+#             */
/*   Updated: 2023/01/12 18:52:01 by rania            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
void *thread_1(pthread_mutex_t forks[2])
{
	pthread_mutex_lock(&forks[0]);
	pthread_mutex_lock(&forks[1]);
	printf("Je suis un philo qui graille.\n");
	pthread_mutex_unlock(&forks[0]);
	pthread_mutex_unlock(&forks[1]);
	return NULL;
}
int main(void)
{
	// t_stack	*table;

	// if (ac != 5 && ac != 6)
	// {
	// 	printf(RED"Bad number of args.\n"WHITE);
	// 	return (0);
	// }
	// if (!ft_check_arg(av))
	// 	return (0);
	// table = ft_fill_table(av, ac);
	pthread_t	philo[2];
	pthread_mutex_t    forks[2];
	int			i;

	i = -1;
	pthread_mutex_init(&forks[0], NULL);
	pthread_mutex_init(&forks[1], NULL);
	while(++i < 2)
	{
		pthread_create(&philo[i], NULL, thread_1, forks);
	}
	i = -1;
	while(++i < 2)
	{
		pthread_join(philo[i], NULL);
		pthread_mutex_destroy(&forks[i]);
	}
	return (0);
}
