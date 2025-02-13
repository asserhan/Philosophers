/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasserao <hasserao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 02:35:51 by hasserao          #+#    #+#             */
/*   Updated: 2023/05/19 03:36:54 by hasserao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&philo->meals_eaten_mutex);
		if (philo->meals_eaten == philo->data->num_eat)
		{
			pthread_mutex_unlock(&philo->meals_eaten_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->meals_eaten_mutex);
		pthread_mutex_lock(&philo->data->is_dead_mutex);
		if (philo->data->is_dead == 1)
		{
			pthread_mutex_unlock(&philo->data->is_dead_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->data->is_dead_mutex);
		if (one_philo(philo))
			return (NULL);
		ft_eating(philo);
		ft_sleeping(philo);
	}
	return (NULL);
}

void	*ft_routine_2(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&philo->meals_eaten_mutex);
		if (philo->meals_eaten == philo->data->num_eat)
		{
			pthread_mutex_unlock(&philo->meals_eaten_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->meals_eaten_mutex);
		pthread_mutex_lock(&philo->data->is_dead_mutex);
		if (philo->data->is_dead == 1)
		{
			pthread_mutex_unlock(&philo->data->is_dead_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->data->is_dead_mutex);
		if (one_philo(philo))
			return (NULL);
		ft_sleeping(philo);
		ft_eating(philo);
	}
	return (NULL);
}

void	*ft_check_eat(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (ft_meals(philo))
			return (NULL);
	}
	return (NULL);
}

int	supervisor(t_data *data)
{
	pthread_t	tid;

	if (pthread_create(&tid, NULL, &ft_check_eat, data->philo))
		return (ft_error_msg(data));
	if (pthread_join(tid, NULL))
		return (ft_error_msg(data));
	return (0);
}

int	the_routine(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_philo)
	{
		pthread_mutex_lock(&data->start_time_mutex);
		data->start_time = ft_get_time();
		pthread_mutex_unlock(&data->start_time_mutex);
		if (i % 2 == 0)
		{
			if (pthread_create(&data->philo[i].thread, NULL, &ft_routine,
					&data->philo[i]))
				return (ft_error_msg(data));
		}
		else
		{
			if (pthread_create(&data->philo[i].thread, NULL, &ft_routine_2,
					&data->philo[i]))
				return (ft_error_msg(data));
		}
	}
	return (0);
}
