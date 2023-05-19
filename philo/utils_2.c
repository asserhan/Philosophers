/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasserao <hasserao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 02:42:44 by hasserao          #+#    #+#             */
/*   Updated: 2023/05/19 04:05:38 by hasserao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	one_philo(t_philo *philo)
{
	if (philo->data->num_philo == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		ft_print_mutex(philo, "has taken a fork");
		pthread_mutex_lock(&philo->last_eat_time_mutex);
		philo->last_eat_time = ft_get_time();
		pthread_mutex_unlock(&philo->last_eat_time_mutex);
		return (1);
	}
	return (0);
}

void	ft_check_meals(t_philo *philo, int i, int done)
{
	pthread_mutex_lock(&philo[i].meals_eaten_mutex);
	if (philo[i].meals_eaten == philo->data->num_eat)
	{
		pthread_mutex_unlock(&philo[i].meals_eaten_mutex);
		done++;
	}
	pthread_mutex_unlock(&philo[i].meals_eaten_mutex);
}
