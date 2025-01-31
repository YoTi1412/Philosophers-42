/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrafai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 00:53:43 by yrafai            #+#    #+#             */
/*   Updated: 2025/01/27 00:53:45 by yrafai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_args *args, t_philo *philo)
{
	pthread_mutex_lock(&philo->last_m);
	if (get_time() - philo->last_meal_time >= args->time_to_die)
	{
		pthread_mutex_lock(&args->print_mutex);
		pthread_mutex_lock(&args->dead_mutex);
		args->dead = 1;
		pthread_mutex_unlock(&args->dead_mutex);
		printf("%zu %d died\n", get_time() - args->start, philo->id);
		pthread_mutex_unlock(&args->print_mutex);
		pthread_mutex_unlock(&philo->last_m);
		return (1);
	}
	pthread_mutex_unlock(&philo->last_m);
	return (0);
}

void	update_full_flag(t_args *args)
{
	pthread_mutex_lock(&args->full_mutex);
	args->full_flag = 1;
	pthread_mutex_unlock(&args->full_mutex);
}

void	*monitor(t_args *args)
{
	size_t	i;

	while (1)
	{
		i = -1;
		while (++i < args->philo_n)
		{
			pthread_mutex_lock(&args->philos[i].counter_mutex);
			if (args->n_lim_meals <= args->philos[i].meals_counter)
			{
				args->all_meals_eaten++;
				if (args->all_meals_eaten >= args->philo_n)
				{
					pthread_mutex_unlock(&args->philos[i].counter_mutex);
					update_full_flag(args);
					return (NULL);
				}
				pthread_mutex_unlock(&args->philos[i].counter_mutex);
			}
			pthread_mutex_unlock(&args->philos[i].counter_mutex);
			if (is_dead(args, &args->philos[i]))
				return (NULL);
		}
	}
	return (NULL);
}
