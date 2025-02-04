/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrafai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 00:54:15 by yrafai            #+#    #+#             */
/*   Updated: 2025/01/27 00:54:17 by yrafai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_usleep(size_t milliseconds, t_args *args)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < milliseconds)
	{
		pthread_mutex_lock(&args->dead_mutex);
		if (args->dead == 1)
			return (pthread_mutex_unlock(&args->dead_mutex), 0);
		pthread_mutex_unlock(&args->dead_mutex);
		usleep(500);
	}
	return (0);
}

size_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		printf("gettimeofday() error\n");
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	tiny_check(t_args args)
{
	if (args.philo_n == 0 || args.time_to_die == 0
		|| args.time_to_eat == 0 || args.time_to_sleep == 0
		|| args.n_lim_meals == 0)
		return (1);
	return (0);
}
