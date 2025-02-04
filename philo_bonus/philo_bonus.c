/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrafai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 00:54:43 by yrafai            #+#    #+#             */
/*   Updated: 2025/01/27 00:54:44 by yrafai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	data_init(t_args *args)
{
	size_t	i;

	sem_unlink("forks");
	sem_unlink("print_sem");
	sem_unlink("last_m_sem");
	sem_unlink("counter_sem");
	args->forks = sem_open("forks", O_CREAT, 0644, args->philo_n);
	args->print_sem = sem_open("print_sem", O_CREAT, 0644, 1);
	args->last_m_sem = sem_open("print_sem", O_CREAT, 0644, 1);
	args->counter_sem = sem_open("counter_sem", O_CREAT, 0644, 1);
	i = -1;
	while (++i < args->philo_n)
	{
		args->philos[i].id = i + 1;
		args->philos[i].pid = -1;
		args->philos[i].meals_counter = 0;
		args->philos[i].args = args;
		args->start = get_time();
	}
}

int	create_processes(t_args *args)
{
	size_t	i;

	i = -1;
	while (++i < args->philo_n)
	{
		sem_wait(args->last_m_sem);
		args->philos[i].last_meal_time = get_time();
		sem_post(args->last_m_sem);
		args->philos[i].pid = fork();
		if (args->philos[i].pid == 0)
			routine(args, &args->philos[i]);
		else if (args->philos[i].pid < 0)
		{
			printf("Error: fork failed\n");
			return (0);
		}
	}
	return (1);
}

void	kill_and_close(t_args *args)
{
	size_t	i;
	int		status;

	status = 0;
	i = -1;
	while (++i < args->philo_n)
	{
		waitpid(-1, &status, 0);
		if (WEXITSTATUS(status))
		{
			i = -1;
			while (++i < args->philo_n)
				kill(args->philos[i].pid, SIGKILL);
			break ;
		}
	}
	sem_close(args->forks);
	sem_close(args->print_sem);
	sem_close(args->last_m_sem);
	sem_close(args->counter_sem);
	sem_unlink("forks");
	sem_unlink("print_sem");
	sem_unlink("last_m_sem");
	sem_unlink("counter_sem");
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
		if (args->philo_n == 0 || args->time_to_die == 0
			|| args->time_to_eat == 0 || args->time_to_sleep == 0
			|| (ac == 6 && args->n_lim_meals == 0))
			return (free(args), 1);
		args->philos = malloc(sizeof(t_philo) * args->philo_n);
		if (!args->philos)
			return (free(args), 1);
		data_init(args);
		if (!create_processes(args))
			return (free(args->philos), free(args), 1);
		kill_and_close(args);
		free(args->philos);
		free(args);
	}
	else
		return (printf("Error: Wrong number of arguments\n"), 1);
	return (0);
}
