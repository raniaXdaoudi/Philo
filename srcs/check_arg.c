/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rania <rania@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 17:43:24 by rania             #+#    #+#             */
/*   Updated: 2023/01/12 17:49:46 by rania            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_arg(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
				if(!ft_isdigit(av[i][j]))
				{
					printf(RED"Args must contains only digits.\n"WHITE);
					return (0);
				}
				j++;
		}
		i++;
	}
	if (ft_atoi(av[1]) < 1)
	{
		printf(RED"Bad number of philo.\n"WHITE);
		return (0);
	}
	return (1);
}
