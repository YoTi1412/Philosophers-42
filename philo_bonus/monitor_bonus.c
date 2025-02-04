/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrafai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 00:54:31 by yrafai            #+#    #+#             */
/*   Updated: 2025/01/27 00:54:33 by yrafai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	is_dead(t_args *args, t_philo *philo)
{
	sem_wait(args->last_m_sem);
	if (get_time() - philo->last_meal_time >= args->time_to_die)
	{
		printf("%zu %d died\n", get_time() - args->start, philo->id);
		sem_post(args->last_m_sem);
		return (1);
	}
	sem_post(args->last_m_sem);
	return (0);
}

void	*monitor(void *argss)
{
	t_args	*args;

	args = (t_args *)argss;
	while (1)
	{
		usleep(100);
		sem_wait(args->counter_sem);
		if (args->philos[args->index].meals_counter >= args->n_lim_meals)
		{
			sem_post(args->counter_sem);
			exit(0);
		}
		sem_post(args->counter_sem);
		if (is_dead(args, args->philos + args->index))
			exit(1);
	}
	return (NULL);
}
