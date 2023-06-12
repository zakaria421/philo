/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 14:58:33 by zbentale          #+#    #+#             */
/*   Updated: 2023/06/12 16:52:29 by zbentale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	infiniteloop(t_philo *structphilo, t_const *constphilo)
{
	while (1)
	{
		if (constphilo->times_to_each_phile_eat != -1
			&& ft_alleaten(structphilo) == 1)
			break ;
		if (philodeath(structphilo) == 1)
			break ;
	}
}

void	initialize(t_all *all, t_philo *structphilo)
{
	int	i;

	i = 0;
	gettimeofday(&all->start_time, NULL);
	while (i < all->constphilo->num_philo)
	{
		structphilo[i].constphilo = all->constphilo;
		structphilo[i].fork = all->fork;
		structphilo[i].id = i + 1;
		structphilo[i].start_time = all->start_time;
		structphilo[i].times_eaten = 0;
		structphilo[i].last_eaten = get_timedeath();
		structphilo[i].print = all->print;
		structphilo[i].test = all->test;
		i++;
	}
}

void	create_threads(t_all *all, t_philo *structphilo, pthread_t *philo)
{
	int	i;

	i = 0;
	while (i < all->constphilo->num_philo)
	{
		pthread_create(&philo[i], NULL, &philofun, &structphilo[i]);
		pthread_detach(philo[i]);
		i++;
	}
}

void	create_forks(t_all *all)
{
	int	i;

	i = 0;
	pthread_mutex_init(all->print, NULL);
	pthread_mutex_init(all->test, NULL);
	while (i < all->constphilo->num_philo)
	{
		pthread_mutex_init(&all->fork[i], NULL);
		i++;
	}
}
