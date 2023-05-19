/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasserao <hasserao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 21:50:10 by hasserao          #+#    #+#             */
/*   Updated: 2023/05/19 02:39:01 by hasserao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_meals(t_philo *philo)
{
	int	i;
	int	done;

	i = -1;
	done = 0;
	while (++i < philo->data->num_philo)
	{
		pthread_mutex_lock(&philo[i].last_eat_time_mutex);
		if (ft_get_time() - philo[i].last_eat_time > philo->data->t_to_die)
		{
			pthread_mutex_unlock(&philo[i].last_eat_time_mutex);
			ft_print_mutex(philo, "died");
			pthread_mutex_lock(&philo->data->is_dead_mutex);
			philo->data->is_dead = 1;
			pthread_mutex_unlock(&philo->data->is_dead_mutex);
			pthread_mutex_lock(&philo->data->print);
			return (1);
		}
		pthread_mutex_unlock(&philo[i].last_eat_time_mutex);
		pthread_mutex_lock(&philo[i].meals_eaten_mutex);
		if (philo[i].meals_eaten == philo->data->num_eat)
		{
			pthread_mutex_unlock(&philo[i].meals_eaten_mutex);
			done++;
		}
		pthread_mutex_unlock(&philo[i].meals_eaten_mutex);
	}
	if (done == philo->data->num_philo)
		return (1);
	return (0);
}

void	ft_destroy(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_detach(data->philo[i].thread);
	}
	pthread_mutex_destroy(&data->print);
	if (data->forks != NULL)
		free(data->forks);
	if (data->philo != NULL)
		free(data->philo);
	if (data != NULL)
		free(data);
}

int	ft_error_msg(t_data *data)
{
	write(2, "Error\n", 6);
	if (data)
		ft_destroy(data);
	return (1);
}

int	ft_dinning(t_data *data)
{
	int	i;

	if (the_routine(data))
		return (ft_error_msg(data));
	if (supervisor(data))
		return (ft_error_msg(data));
	i = -1;
	while (++i < data->num_philo)
	{
		if (pthread_join(data->philo[i].thread, NULL))
			return (ft_error_msg(data));
	}
	return (0);
}
int	main(int argc, char **argv)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (ft_error_msg(data));
	memset(data, 0, sizeof(t_data));
	if (argc < 5 || argc > 6)
		return (ft_error_msg(data));
	if (ft_parsing(argc, argv))
		return (ft_error_msg(data));
	if (ft_init(data, argc, argv))
		return (1);
	if (ft_dinning(data))
		return (ft_error_msg(data));
	ft_destroy(data);
	return (0);
}
