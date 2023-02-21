/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rania <rania@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 15:39:40 by rania             #+#    #+#             */
/*   Updated: 2023/02/21 14:01:29 by rania            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t	get_current_time(void)
{
	struct timeval	tval;

	gettimeofday(&tval, NULL);
	return ((tval.tv_sec * 1000) + (tval.tv_usec / 1000));
}

void	wait_time(t_stack *table, time_t time)
{
	while (get_current_time() < time)
	{
		if (table->died)
			return ;
		usleep(1000);
	}
}
