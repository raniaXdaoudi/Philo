/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rania <rania@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 17:43:31 by rania             #+#    #+#             */
/*   Updated: 2023/01/09 18:14:27 by rania            ###   ########.fr       */
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

int main(int ac, char **av)
{
	t_stack	*table;

	if (ac != 5 && ac != 6)
	{
		printf(RED"Bad number of args.\n"WHITE);
		return (0);
	}
	if (!ft_check_arg(av))
		return (0);
	table = ft_fill_table(av, ac);
	return (0);
}
