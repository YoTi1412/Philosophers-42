/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrafai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 00:53:49 by yrafai            #+#    #+#             */
/*   Updated: 2025/01/27 00:53:51 by yrafai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

int	is_space(char c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

char	*check_input(char *str)
{
	char	*tmp;

	tmp = str;
	while (*tmp && is_space(*tmp))
		tmp++;
	if (!*tmp)
		return (NULL);
	if (*tmp == '+')
		tmp++;
	while (*tmp && is_digit(*tmp))
		tmp++;
	while (*tmp)
	{
		if (!is_space(*tmp))
			return (NULL);
		tmp++;
	}
	if (!*tmp)
		return (str);
	return (NULL);
}

size_t	ft_atol(char *str)
{
	size_t	result;

	result = 0;
	if (!check_input(str))
	{
		printf("Error: Invalid argument\n");
		return (0);
	}
	while (*str && is_space(*str))
		str++;
	if (*str == '+')
		str++;
	while (str && is_digit(*str))
	{
		result = result * 10 + *str - '0';
		if (result > INT_MAX)
		{
			printf("Error: Argument out of range\n");
			return (0);
		}
		str++;
	}
	return (result);
}

void	parse_input(t_args *args, char **av)
{
	args->philo_n = ft_atol(av[1]);
	if (args->philo_n == 0)
		return ;
	args->time_to_die = ft_atol(av[2]);
	if (args->time_to_die == 0)
		return ;
	args->time_to_eat = ft_atol(av[3]);
	if (args->time_to_eat == 0)
		return ;
	args->time_to_sleep = ft_atol(av[4]);
	if (args->time_to_sleep == 0)
		return ;
	if (av[5])
		args->n_lim_meals = ft_atol(av[5]);
	else
		args->n_lim_meals = -1;
}
