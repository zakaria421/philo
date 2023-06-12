/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 13:34:02 by zbentale          #+#    #+#             */
/*   Updated: 2023/06/11 11:49:08 by zbentale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_alleaten(t_philo *structphilo)
{
	int	i;

	i = 0;
	while (i < structphilo->constphilo->num_philo)
	{
		pthread_mutex_lock(structphilo->test);
		if (structphilo[i].times_eaten
			< structphilo->constphilo->times_to_each_phile_eat)
		{
			pthread_mutex_unlock(structphilo->test);
			return (0);
		}
		pthread_mutex_unlock(structphilo->test);
		i++;
	}
	return (1);
}

int	check_arg1(t_const *constphilo)
{
	if (constphilo->num_philo == 0 || constphilo->time_to_die == 0
		|| constphilo->time_to_eat == 0 || constphilo->time_to_sleep == 0
		|| constphilo->times_to_each_phile_eat == 0)
	{
		printf("Error: Wrong arguments\n");
		return (1);
	}
	return (0);
}

int	check_arg(int argc)
{
	if (argc < 5 || argc > 6)
	{
		printf("Error: Wrong number of arguments\n");
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	pthread_t	*philo;
	t_philo		*structphilo;
	t_all		*all;

	if (check_arg(argc) == 1)
		return (1);
	all = malloc(sizeof(t_all));
	all->constphilo = malloc(sizeof(t_const));
	init_const(all->constphilo, argc, argv);
	if (check_arg1(all->constphilo) == 1)
		return (1);
	philo = malloc(sizeof(pthread_t) * all->constphilo->num_philo);
	all->fork = malloc(sizeof(pthread_mutex_t) * all->constphilo->num_philo);
	structphilo = malloc(sizeof(t_philo) * all->constphilo->num_philo);
	all->print = malloc(sizeof(pthread_mutex_t));
	all->test = malloc(sizeof(pthread_mutex_t));
	create_forks(all);
	initialize(all, structphilo);
	create_threads(all, structphilo, philo);
	infiniteloop(structphilo, all->constphilo);
	free(all->constphilo);
	return (0);
}
