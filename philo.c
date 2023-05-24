/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 13:34:02 by zbentale          #+#    #+#             */
/*   Updated: 2023/05/23 21:50:59 by zbentale         ###   ########.fr       */
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

long get_timeDeath(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) +(current_time.tv_usec / 1000));
}

void	*philofun(void *arg)
{
	t_philo	*structphilo;
	int j = 0;

	structphilo = (t_philo *)arg;
	if (structphilo->id % 2 == 0)
		usleep(100);
	while (structphilo->constphilo->death)
	{
		pthread_mutex_lock(&structphilo->fork[(structphilo->id - 1)]);
		printstr("has taken a fork",structphilo);
		pthread_mutex_lock(&structphilo->fork[structphilo->id
				% structphilo->constphilo->num_philo]);
		printstr("has taken a fork",structphilo);
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

int	ft_alleaten(t_philo *structphilo)
{
	int	i;

	i = 0;
	while (i < structphilo->constphilo->num_philo)
	{
		if (structphilo[i].times_eaten < structphilo->constphilo->times_to_each_phile_eat)
			return (0);
		i++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_const *constphilo;
	struct timeval start_time;
	int i = 0;
	if (argc < 5 || argc > 6)
	{
		printf("Error: Wrong number of arguments\n");
		return (1);
	}
	constphilo = malloc(sizeof(t_const));
	init_const(constphilo, argc, argv);
	if (constphilo->num_philo == 0 || constphilo->time_to_die == 0
		|| constphilo->time_to_eat == 0 || constphilo->time_to_sleep == 0
		|| constphilo->times_to_each_phile_eat == 0)
	{
		printf("Error: Wrong arguments\n");
		return (1);
	}
	// id table
	//pthread_t philo[constphilo->num_philo];
	pthread_t *philo;
	philo=malloc(sizeof(pthread_t) * constphilo->num_philo);
	//frchat table
	// pthread_mutex_t fork[constphilo->num_philo];
	pthread_mutex_t *fork;
	fork=malloc(sizeof(pthread_mutex_t) * constphilo->num_philo);
	pthread_mutex_t *print;
	// t_philo structphilo[constphilo->num_philo];
	t_philo *structphilo;
	structphilo=malloc(sizeof(t_philo) * constphilo->num_philo);
	print=malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(print, NULL);
	//init mutex

	while (i < constphilo->num_philo)
	{
		pthread_mutex_init(&fork[i], NULL);
		i++;
	}
	//create thread
	//init struct
	i = 0;
	gettimeofday(&start_time, NULL);
	
	while (i < constphilo->num_philo)
	{
		structphilo[i].constphilo = constphilo;
		structphilo[i].fork = fork;
		structphilo[i].id = i + 1;
		structphilo[i].start_time = start_time;
		structphilo[i].times_eaten = 0;
		structphilo[i].last_eaten = get_timeDeath();
		structphilo[i].print = print;
		i++;
	}
	structphilo->constphilo->death = 1;
	i = 0;

	while (i < constphilo->num_philo)
	{
		pthread_create(&philo[i], NULL, &philofun, &structphilo[i]);
		pthread_detach(philo[i]);
		i++;
		
	}

	while (1)
	{
		
		if (constphilo->times_to_each_phile_eat != -1
			&& ft_alleaten(structphilo) == 1)
			break ;
		if(philodeath(structphilo) == 1)
			break ;
	}
	
	//destroy mutex
	//sleep(2);
	// while (i < constphilo->num_philo)
	// {
	// 	pthread_mutex_destroy(&fork[i]);
	// 	i++;
	// }
	//free
	free(constphilo);

	return (0);
}