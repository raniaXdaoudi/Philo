/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rania <rania@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 17:43:31 by rania             #+#    #+#             */
/*   Updated: 2023/02/13 11:51:14 by rania            ###   ########.fr       */
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
	if (pthread_mutex_init(&table->print, NULL) != 0)
		return (NULL);
	table->start_time = 0;
	table->died = 0;
	if(ac == 6)
		table->nb_meal = ft_atoi(av[5]);
	return (table);
}

void	ft_print(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->table->print);
	ft_putnbr(get_current_time() - philo->table->start_time);
	write(1, " ", 1);
	ft_putnbr(philo->id + 1);
	write(1, " ", 1);
	write(1, str, ft_strlen(str));
	pthread_mutex_unlock(&philo->table->print);
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
		ft_putnbr(get_current_time() - philo->table->start_time);
		write(1, " ", 1);
		ft_putnbr(philo->id + 1);
		write(1, " ", 1);
		write(1, "died.\n", ft_strlen("died.\n"));
		philo->table->died = 1;
		pthread_mutex_unlock(&philo->table->print);
		return (0);
	}
	pthread_mutex_unlock(&philo->table->print);
	return (1);
}

void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	philo->last_eat = philo->table->start_time;
	if (philo->id % 2 == 0)
		usleep(philo->table->time_eat * 1000);
	while (get_death(philo))
	{
		if (!get_death(philo))
			return (NULL);
		pthread_mutex_lock(&philo->table->forks[philo->forks[0]]);
		ft_print(philo, "has taken a fork.\n");
		pthread_mutex_lock(&philo->table->forks[philo->forks[1]]);
		ft_print(philo, "has taken a fork.\n");
		ft_print(philo, "is eating.\n");
		philo->last_eat = get_current_time();
		wait_time(philo->table, get_current_time() + philo->table->time_eat);
		philo->eat_count += 1;
		pthread_mutex_unlock(&philo->table->forks[philo->forks[0]]);
		pthread_mutex_unlock(&philo->table->forks[philo->forks[1]]);
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
		philo[i]->last_eat = 0;
		philo[i]->eat_count = 0;
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

	i = 0;
	if (table->nb_philo == 1)
	{
		ft_print(*philo, "has taken a fork.\n");
		usleep(table->time_die * 1000);
		printf("%lu %i died\n", get_current_time() - table->start_time, philo[0]->id + 1);
		return ;
	}
	while (i < table->nb_philo)
	{
		pthread_create(&philo[i]->thread, NULL, routine, philo[i]);
		i += 1;
	}
}

void	*routine_death(void *data)
{
	t_philo	**philo;
	int		i;
	int		check_eat_count;

	philo = (t_philo **)data;
	usleep(philo[0]->table->time_die * 1000);
	while (1)
	{
		i = 0;
		check_eat_count = 1;
		while(i < philo[0]->table->nb_philo)
		{
			if (philo[i]->eat_count <= philo[0]->table->nb_meal)
				check_eat_count = 0;
			if (!get_death(philo[i]))
				return (NULL);
			i++;
		}
		if (check_eat_count == 1)
		{
			philo[0]->table->died = 1;
			return (NULL);
		}
	}
	return (NULL);
}

int main(int ac, char **av)
{
	t_stack		*table;
	t_philo		**philo;
	pthread_t	death;
	int			i;

	if (ac != 5 && ac != 6)
	{
		printf(RED"Bad number of args.\n"WHITE);
		return (0);
	}
	if (!ft_check_arg(av))
		return (0);
	table = ft_fill_table(av, ac);
	philo = ft_init_philo(table);
	table->start_time = get_current_time();
	ft_open_thread(philo, table);
	if (table->nb_philo > 1)
		pthread_create(&death, NULL, routine_death, philo);
	pthread_join(death, NULL);
	i = 0;
	while(i < table->nb_philo)
	{
		pthread_join(philo[i]->thread, NULL);
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	return (0);
}
