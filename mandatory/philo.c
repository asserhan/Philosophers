/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasserao <hasserao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 02:35:51 by hasserao          #+#    #+#             */
/*   Updated: 2023/05/07 15:28:19 by hasserao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long long  ft_get_time()
{
	struct timeval currentTime;
	gettimeofday(&currentTime, NULL);
	return (currentTime.tv_sec * 1000 + currentTime.tv_usec / 1000);
}
void ft_routine(void *arg)
{
	t_philo *philo;
	philo = (t_philo *)arg;
	if (philo->is_dead)
	{
		
	}

}
int ft_dinning(t_data *data)
{
	int i;
	i = -1;
	data->debut_time = ft_get_time();
	while (++i < data->num_philo)
	{
		if(pthread_create(&data->philo[i].thread,NULL,&ft_routine,&data->philo[i]))
	}

}
