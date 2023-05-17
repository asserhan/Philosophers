/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasserao <hasserao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 15:14:36 by hasserao          #+#    #+#             */
/*   Updated: 2023/05/17 23:40:30 by hasserao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int all_philos_eaten(t_philo *philo)
{
	if(philo->data->num_philo == philo->data->eaten_philos)
		return(0);
	return(1);
}

int ft_usleep(long long time)
{
	long long start;
	start = ft_get_time();
	while(ft_get_time() - start < time)
		usleep(100);
	return(0);
}

void ft_print_mutex(t_philo *philo,char *str)
{
	if(philo->data->is_dead != 0 || all_philos_eaten(philo) == 0)
		return ;
	pthread_mutex_lock(&philo->data->print);
	printf("%lld %d %s\n",ft_get_time()- philo->data->start_time,philo->id,str);
	pthread_mutex_unlock(&philo->data->print);
}
void ft_eating(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	ft_print_mutex(philo,"has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	ft_print_mutex(philo,"has taken a fork");
	pthread_mutex_lock(&philo->eat_mutex);
	ft_print_mutex(philo,"is eating");
	philo->last_eat_time = ft_get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->eat_mutex);
	ft_usleep(philo->data->t_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	//philo->eating_status = 1;
	//philo->eating_status = 0;

}
void ft_sleeping(t_philo *philo)
{
	//philo->sleep_time = ft_get_time();
	ft_print_mutex(philo,"is sleeping");
	ft_usleep(philo->data->t_to_sleep);
	ft_print_mutex(philo,"is thinking");
}

