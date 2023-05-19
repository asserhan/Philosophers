/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasserao <hasserao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 01:30:16 by hasserao          #+#    #+#             */
/*   Updated: 2023/05/19 02:36:04 by hasserao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_init_forks(t_data *data)
{
	int	i;

	i = -1;
	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* data->num_philo);
	if (!data->forks)
		return (ft_error_msg(data));
	while (++i < data->num_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (ft_error_msg(data));
	}
	return (0);
}

int	ft_init_philo(t_data *data)
{
	int	i;

	i = -1;
	data->philo = (t_philo *)malloc(sizeof(t_philo) * data->num_philo);
	if (!data->philo)
		return (ft_error_msg(data));
	while (++i < data->num_philo)
	{
		if (pthread_mutex_init(&data->philo[i].last_eat_time_mutex, NULL))
			return (ft_error_msg(data));
		if (pthread_mutex_init(&data->philo[i].meals_eaten_mutex, NULL))
			return (ft_error_msg(data));
		/////
		data->philo[i].id = i + 1;
		data->philo[i].right_fork = &data->forks[i];
		data->philo[i].left_fork = &data->forks[(i + 1) % data->num_philo];
		data->philo[i].last_eat_time = ft_get_time();
		data->philo[i].meals_eaten = 0;
		data->philo[i].data = data;
	}
	return (0);
}

int	ft_init(t_data *data, int argc, char **argv)
{
	data->num_philo = ft_atoi(argv[1]);
	data->t_to_die = ft_atoi(argv[2]);
	data->t_to_eat = ft_atoi(argv[3]);
	data->t_to_sleep = ft_atoi(argv[4]);
	data->is_dead = 0;
	if (pthread_mutex_init(&data->start_time_mutex, NULL))
		return (1);
	if (pthread_mutex_init(&data->print, NULL))
		return (1);
	if (pthread_mutex_init(&data->is_dead_mutex, NULL))
		return (1);
	if (ft_init_forks(data))
		return (ft_error_msg(data));
	if (ft_init_philo(data))
		return (ft_error_msg(data));

	if (data->num_philo <= 0 || data->t_to_die <= 0 || data->t_to_eat <= 0
		|| data->t_to_sleep <= 0)
		return (ft_error_msg(data));
	if (argc == 6)
	{
		data->num_eat = ft_atoi(argv[5]);
		if (data->num_eat <= 0)
			return (ft_error_msg(data));
	}
	else
		data->num_eat = -1;
	return (0);
}
