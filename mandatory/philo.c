/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasserao <hasserao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 02:35:51 by hasserao          #+#    #+#             */
/*   Updated: 2023/05/16 21:54:06 by hasserao         ###   ########.fr       */
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
	while (philo->data->is_dead == 0)
	{
		ft_eating(philo);
		ft_sleeping(philo);
	}
	if(pthread_join(philo->thread,NULL))
		return (NULL);
	return (NULL);
}
void *ft_check_eat(void *arg)
{
	t_philo *philo;
	philo = (t_philo *)arg;
	while (philo->data->is_dead == 0)
	{
		if(philo->data->t_to_die < ft_get_time() - philo->last_eat_time)
		{
			pthread_mutex_lock(&philo->data->print);
			ft_print_mutex(philo,"died");
			philo->data->is_dead = 1;
			philo->data->game_over = 1;
			pthread_mutex_unlock(&philo->data->print);
			return (NULL);
		}
		if(philo->count_eat == philo->data->num_eat * philo->data->num_philo)
		{
			philo->data->game_over = 1;
			return (NULL);
		}
		usleep(100);
	}
	return (NULL);
}
int ft_dinning(t_data *data)
{
	int i;
	i = -1;
	pthread_t tid;

	data->start_time = ft_get_time();
	if(data->num_eat != -1)
	{
		while(++i < data->num_philo)
		{
			if(pthread_create(&tid,NULL,&ft_check_eat,&data->philo[i]))
				return (ft_error_msg(data));
			usleep(110);
		}
	}
	i = -1;
	while (++i < data->num_philo)
	{
		data->philo[i].last_eat_time = ft_get_time();
		if(pthread_create(&data->philo[i].thread,NULL,&ft_routine,&data->philo[i]))
			return (ft_error_msg(data));
		usleep(110);
	}
	i = -1;
	while (++i < data->num_philo)
	{
		if(pthread_join(data->philo[i].thread,NULL))
			return (ft_error_msg(data));
	}
	return(0);
}
