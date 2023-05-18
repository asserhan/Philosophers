/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasserao <hasserao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 02:35:51 by hasserao          #+#    #+#             */
/*   Updated: 2023/05/18 16:41:38 by hasserao         ###   ########.fr       */
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
	pthread_mutex_lock(&philo->data->game_over_mutex);
	while (philo->data->is_dead == 0  && philo->meals_eaten != philo->data->num_eat)
	{
		//printf("%d\n",philo->data->game_over);
		pthread_mutex_unlock(&philo->data->game_over_mutex);
		if(philo->data->num_philo == 1)
		{
			pthread_mutex_lock(philo->left_fork);
			ft_print_mutex(philo,"has taken a fork");
			philo->last_eat_time = ft_get_time();
			return (NULL);
		}
		ft_eating(philo);
		ft_sleeping(philo);
		pthread_mutex_lock(&philo->data->game_over_mutex);
	}
	pthread_mutex_unlock(&philo->data->game_over_mutex);
	// if(pthread_join(philo->thread,NULL))
	// 	return (NULL);
	return (NULL);
}
void *ft_routine_2(void *arg)
{
	t_philo *philo;
	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->data->game_over_mutex);
	while (philo->data->is_dead == 0 && philo->meals_eaten != philo->data->num_eat)
	{
		pthread_mutex_unlock(&philo->data->game_over_mutex);
		if(philo->data->num_philo == 1)
		{
			pthread_mutex_lock(philo->left_fork);
			ft_print_mutex(philo,"has taken a fork");
			philo->last_eat_time = ft_get_time();
			return (NULL);
		}
		ft_sleeping(philo);
		ft_eating(philo);
		pthread_mutex_lock(&philo->data->game_over_mutex);
	}
	pthread_mutex_unlock(&philo->data->game_over_mutex);
	// if(pthread_join(philo->thread,NULL))
	// 	return (NULL);
	return (NULL);
}
void *ft_check_eat(void *arg)
{
	t_philo *philo;
	philo = (t_philo *)arg;
	int i;
	int done;
	while (1)
	{
		i = -1;
		done = 0;
		while(++i < philo->data->num_philo)
		{
			pthread_mutex_lock(&philo->eat_mutex);
			if(ft_get_time() - philo[i].last_eat_time > philo->data->t_to_die)
			{
				// printf("get_time %lld ",ft_get_time() - philo[i].last_eat_time);
				ft_print_mutex(philo,"died");
				philo->data->is_dead = 1;
				pthread_mutex_unlock(&philo->eat_mutex);
				pthread_mutex_lock(&philo->data->print);
				return (NULL);
			}
			pthread_mutex_unlock(&philo->eat_mutex);
			pthread_mutex_lock(&philo[i].meals_eaten_mutex);
			if(philo[i].meals_eaten == philo->data->num_eat)
				done++;
				// philo->data->eaten_philos++;
			pthread_mutex_unlock(&philo[i].meals_eaten_mutex);
		}
		//printf("done %d\n",done);
			if (done == philo->data->num_philo)
				return(NULL);
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
		if(i % 2 == 0)
		{
			if(pthread_create(&data->philo[i].thread,NULL,&ft_routine,&data->philo[i]))
				return (ft_error_msg(data));
		}
		else
		{
			if(pthread_create(&data->philo[i].thread,NULL,&ft_routine_2,&data->philo[i]))
				return (ft_error_msg(data));
		}
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
