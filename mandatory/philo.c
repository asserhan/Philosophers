/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasserao <hasserao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 02:35:51 by hasserao          #+#    #+#             */
/*   Updated: 2023/05/17 23:30:43 by hasserao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long long  ft_get_time()
{
	struct timeval currentTime;
	gettimeofday(&currentTime, NULL);
	return (currentTime.tv_sec * 1000 + currentTime.tv_usec / 1000);
}
void *ft_routine(void *arg)
{
	t_philo *philo;
	philo = (t_philo *)arg;

	while (philo->data->is_dead == 0  && all_philos_eaten(philo))
	{
		if(philo->data->num_philo == 1)
		{
			pthread_mutex_lock(philo->left_fork);
			ft_print_mutex(philo,"has taken a fork");
			ft_print_mutex(philo,"is dead");
			philo->last_eat_time = ft_get_time();
			return (NULL);
		}
		ft_eating(philo);
		ft_sleeping(philo);
	}
	// if(pthread_join(philo->thread,NULL))
	// 	return (NULL);
	return (NULL);
}
void *ft_check_eat(void *arg)
{
	t_philo *philo;
	philo = (t_philo *)arg;
	int i;
	while (all_philos_eaten(philo))
	{
		i = -1;
		while(++i < philo->data->num_philo)
		{
			pthread_mutex_lock(&philo->eat_mutex);
			if(ft_get_time() - philo->last_eat_time >= philo->data->t_to_die)
			{
				ft_print_mutex(philo,"died");
				philo->data->is_dead = 1;
				pthread_mutex_unlock(&philo->eat_mutex);
				return (NULL);
			}
			pthread_mutex_unlock(&philo->eat_mutex);
			if(philo->meals_eaten == philo->data->num_eat * philo->data->num_philo)
				philo->data->eaten_philos++;
		}
	}
	printf("All philos ate\n");
	return (NULL);
}
int supervisor(t_data *data)
{
	pthread_t tid;

	if(pthread_create(&tid,NULL,&ft_check_eat,data->philo))
		return (ft_error_msg(data));
	if(pthread_join(tid,NULL))
		return (ft_error_msg(data));
	return (0);
}
int ft_dinning(t_data *data)
{
	int i;
	i = -1;

	while (++i < data->num_philo)
	{
		data->start_time = ft_get_time();
		if(pthread_create(&data->philo[i].thread,NULL,&ft_routine,&data->philo[i]))
			return (ft_error_msg(data));
	}
	if(supervisor(data))
		return (ft_error_msg(data));
	i = -1;
	while (++i < data->num_philo)
	{
		if(pthread_join(data->philo[i].thread,NULL))
			return (ft_error_msg(data));
	}
	return(0);
}
