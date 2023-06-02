/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 17:18:31 by zbentale          #+#    #+#             */
/*   Updated: 2023/06/01 17:21:06 by zbentale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t	get_time(struct timeval start_time)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000 + current_time.tv_usec / 1000)
		- (start_time.tv_sec * 1000 + start_time.tv_usec / 1000));
}

long	get_timedeath(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

void	*philofun(void *arg)
{
	t_philo	*structphilo;
	int		j;

	j = 0;
	structphilo = (t_philo *)arg;
	if (structphilo->id % 2 == 0)
		usleep(100);
	while (structphilo->constphilo->death)
	{
		pthread_mutex_lock(&structphilo->fork[(structphilo->id - 1)]);
		printstr("has taken a fork", structphilo);
		pthread_mutex_lock(&structphilo->fork[structphilo->id
			% structphilo->constphilo->num_philo]);
		printstr("has taken a fork", structphilo);
		j = eat(structphilo);
		pthread_mutex_unlock(&structphilo->fork[(structphilo->id)
			% structphilo->constphilo->num_philo]);
		pthread_mutex_unlock(&structphilo->fork[structphilo->id - 1]);
		if (j == 1)
			break ;
		time_to_sleep(structphilo);
	}
	return (NULL);
}
