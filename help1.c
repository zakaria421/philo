/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 13:33:58 by zbentale          #+#    #+#             */
/*   Updated: 2023/05/28 19:03:29 by zbentale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int					i;
	int					sign;
	unsigned long long	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - '0';
		if (result > LLONG_MAX && sign == -1)
			return (0);
		else if (result > LLONG_MAX && sign == 1)
			return (-1);
		i++;
	}
	return (result * sign);
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

int	ft_isnumber(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

void	time_to_sleep(t_philo *structphilo)
{
	printstr("is sleeping", structphilo);
	usleepme(structphilo->constphilo->time_to_sleep);
	printstr("is thinking", structphilo);
}

void	printstr(char *str, t_philo *structphilo)
{
	pthread_mutex_lock(structphilo->print);
	printf("%li philo %d %s\n", get_time(structphilo->start_time),
		structphilo->id, str);
	pthread_mutex_unlock(structphilo->print);
}
