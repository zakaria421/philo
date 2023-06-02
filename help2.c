/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 13:37:38 by zbentale          #+#    #+#             */
/*   Updated: 2023/06/02 01:23:58 by zbentale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_const(t_const *constphilo, int argc, char **argv)
{
	if (ft_isnumber(argv[1]) || ft_isnumber(argv[2]) || ft_isnumber(argv[3])
		|| ft_isnumber(argv[4]) || (argc == 6 && ft_isnumber(argv[5])))
	{
		printf("Error: Wrong arguments\n");
		exit(1);
	}
	constphilo->num_philo = ft_atoi(argv[1]);
	constphilo->time_to_die = ft_atoi(argv[2]);
	constphilo->time_to_eat = ft_atoi(argv[3]);
	constphilo->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		constphilo->times_to_each_phile_eat = ft_atoi(argv[5]);
	else
		constphilo->times_to_each_phile_eat = -1;
}

void	usleepme(int time)
{
	struct timeval	start_time;

	gettimeofday(&start_time, NULL);
	while (get_time(start_time) < time)
		usleep(100);
}

int	eat(t_philo *structphilo)
{
	printstr("is eating", structphilo);
	structphilo->last_eaten = get_timedeath();
	structphilo->times_eaten++;
	usleepme(structphilo->constphilo->time_to_eat);
	if (structphilo->times_eaten
		== structphilo->constphilo->times_to_each_phile_eat)
		return (1);
	return (0);
}

int	philodeath(t_philo *structphilo)
{
	long	time_of_die;
	int		i;

	time_of_die = 0;
	i = 0;
	while (i < structphilo->constphilo->num_philo)
	{
		time_of_die = get_timedeath();
		if (time_of_die
			- structphilo[i].last_eaten > structphilo->constphilo->time_to_die)
		{
			structphilo->constphilo->death = 0;
			pthread_mutex_lock(structphilo->print);
			printf("%li philo %d died\n", get_time(structphilo->start_time),
				structphilo[i].id);
			return (1);
		}
		i++;
	}
	return (0);
}
