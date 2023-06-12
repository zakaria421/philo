/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 13:31:17 by zbentale          #+#    #+#             */
/*   Updated: 2023/06/12 14:55:49 by zbentale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct t_const
{
	int				num_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_to_each_phile_eat;
}					t_const;

typedef struct t_philo
{
	int				id;
	int				times_eaten;
	t_const			*constphilo;
	pthread_mutex_t	*fork;
	struct timeval	start_time;
	long			last_eaten;
	pthread_mutex_t	*print;
	pthread_mutex_t	*test;
}					t_philo;

typedef struct t_all
{
	pthread_mutex_t	*print;
	pthread_mutex_t	*test;
	pthread_mutex_t	*fork;
	t_const			*constphilo;
	struct timeval	start_time;
}					t_all;

int					ft_atoi(const char *str);
int					ft_isdigit(int c);
int					ft_isnumber(char *str);
void				time_to_eat(t_philo *structphilo);
void				time_to_sleep(t_philo *structphilo);
void				init_const(t_const *constphilo, int argc, char **argv);
int					eat(t_philo *structphilo);
time_t				get_time(struct timeval start_time);
void				usleepme(int time);
long				get_timedeath(void);
int					philodeath(t_philo *structphilo);
void				printstr(char *str, t_philo *structphilo);
void				infiniteloop(t_philo *structphilo, t_const *constphilo);
void				*philofun(void *arg);
int					ft_alleaten(t_philo *structphilo);
void				initialize(t_all *all, t_philo *structphilo);
void				create_threads(t_all *all, t_philo *structphilo,
						pthread_t *philo);
void				create_forks(t_all *all);

#endif