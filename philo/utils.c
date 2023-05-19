/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasserao <hasserao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 15:14:36 by hasserao          #+#    #+#             */
/*   Updated: 2023/05/19 03:15:16 by hasserao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	ft_get_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}

int	ft_usleep(long long time)
{
	long long	start;

	start = ft_get_time();
	while (ft_get_time() - start < time)
		usleep(100);
	return (0);
}

void	ft_print_mutex(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->data->is_dead_mutex);
	pthread_mutex_lock(&philo->meals_eaten_mutex);
	if (philo->data->is_dead != 0 || philo->meals_eaten == philo->data->num_eat)
	{
		pthread_mutex_unlock(&philo->meals_eaten_mutex);
		pthread_mutex_unlock(&philo->data->is_dead_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->data->is_dead_mutex);
	pthread_mutex_unlock(&philo->meals_eaten_mutex);
	pthread_mutex_lock(&philo->data->print);
	pthread_mutex_lock(&philo->data->start_time_mutex);
	printf("%lld %d %s\n", ft_get_time() - philo->data->start_time, philo->id,
		str);
	pthread_mutex_unlock(&philo->data->start_time_mutex);
	pthread_mutex_unlock(&philo->data->print);
}

void	ft_eating(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	ft_print_mutex(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	ft_print_mutex(philo, "has taken a fork");
	ft_print_mutex(philo, "is eating");
	pthread_mutex_lock(&philo->last_eat_time_mutex);
	philo->last_eat_time = ft_get_time();
	pthread_mutex_unlock(&philo->last_eat_time_mutex);
	pthread_mutex_lock(&philo->meals_eaten_mutex);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meals_eaten_mutex);
	ft_usleep(philo->data->t_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	ft_sleeping(t_philo *philo)
{
	ft_print_mutex(philo, "is sleeping");
	ft_usleep(philo->data->t_to_sleep);
	ft_print_mutex(philo, "is thinking");
}
