/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrafai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 00:53:56 by yrafai            #+#    #+#             */
/*   Updated: 2025/01/27 00:53:57 by yrafai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	data_init(t_args *args)
{
	size_t	i;

	pthread_mutex_init(&args->print_mutex, NULL);
	pthread_mutex_init(&args->dead_mutex, NULL);
	pthread_mutex_init(&args->full_mutex, NULL);
	args->start = get_time();
	args->dead = 0;
	args->full_flag = 0;
	args->all_meals_eaten = 0;
	i = -1;
	while (++i < args->philo_n)
	{
		args->philos[i].id = i + 1;
		args->philos[i].meals_counter = 0;
		args->philos[i].last_meal_time = get_time();
		pthread_mutex_init(&args->forks[i], NULL);
		args->philos[i].right_fork = &args->forks[i];
		args->philos[i].left_fork = &args->forks[(i + 1) % args->philo_n];
		args->philos[i].args = args;
		pthread_mutex_init(&args->philos[i].counter_mutex, NULL);
		pthread_mutex_init(&args->philos[i].last_m, NULL);
		pthread_mutex_init(&args->forks[i], NULL);
	}
}

int	create_join_threads(t_args *args)
{
	size_t	i;

	i = -1;
	while (++i < args->philo_n)
		if (pthread_create(&args->philos[i].thread_id, NULL,
				&routine, &args->philos[i]))
			return (printf("Error while creating Thread\n"), 0);
	i = -1;
	if (pthread_create(&args->monitor_thread, NULL, (void *)monitor, args))
		return (printf("Error while creating Monitor\n"), 0);
	while (++i < args->philo_n)
		if (pthread_join(args->philos[i].thread_id, NULL))
			return (printf("pthread_joined Error\n"), 0);
	if (pthread_join(args->monitor_thread, NULL))
		return (printf("pthread_joined Monitor Error\n"), 0);
	return (1);
}

void	destroy_and_free(t_args *args)
{
	size_t	i;

	i = -1;
	while (++i < args->philo_n)
	{
		pthread_mutex_destroy(&args->forks[i]);
		pthread_mutex_destroy(&args->philos[i].last_m);
		pthread_mutex_destroy(&args->philos[i].counter_mutex);
	}
	pthread_mutex_destroy(&args->print_mutex);
	pthread_mutex_destroy(&args->dead_mutex);
	pthread_mutex_destroy(&args->full_mutex);
	free(args->forks);
	free(args->philos);
	free(args);
}

int	main(int ac, char **av)
{
	t_args	*args;

	if (ac == 5 || ac == 6)
	{
		args = malloc(sizeof(t_args));
		if (!args)
			return (1);
		parse_input(args, av);
		if (tiny_check(*args))
			return (free(args), 1);
		args->forks = malloc(sizeof(pthread_mutex_t) * args->philo_n);
		if (!args->forks)
			return (free(args), 1);
		args->philos = malloc(sizeof(t_philo) * args->philo_n);
		if (!args->philos)
			return (free(args->forks), free(args), 1);
		data_init(args);
		if (!create_join_threads(args))
			return (destroy_and_free(args), 1);
		destroy_and_free(args);
	}
	else
		return (printf("Error: Wrong number of arguments\n"), 1);
	return (0);
}
