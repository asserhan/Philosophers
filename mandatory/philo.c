/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasserao <hasserao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 02:35:51 by hasserao          #+#    #+#             */
/*   Updated: 2023/05/18 20:56:53 by hasserao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*ft_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->data->is_dead == 0
		&& philo->meals_eaten != philo->data->num_eat)
	{
		if (philo->data->num_philo == 1)
		{
			pthread_mutex_lock(philo->left_fork);
			ft_print_mutex(philo, "has taken a fork");
			philo->last_eat_time = ft_get_time();
			return (NULL);
		}
		ft_eating(philo);
		ft_sleeping(philo);
	}
	return (NULL);
}

void	*ft_routine_2(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->data->is_dead == 0
		&& philo->meals_eaten != philo->data->num_eat)
	{
		if (philo->data->num_philo == 1)
		{
			pthread_mutex_lock(philo->left_fork);
			ft_print_mutex(philo, "has taken a fork");
			philo->last_eat_time = ft_get_time();
			return (NULL);
		}
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
		data->start_time = ft_get_time();
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
