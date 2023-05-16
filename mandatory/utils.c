/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasserao <hasserao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 15:14:36 by hasserao          #+#    #+#             */
/*   Updated: 2023/05/16 22:57:35 by hasserao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int all_philos_eaten(t_philo *philo)
{
	if(philo->data->num_philo == philo->data->eaten_philos)
		return(0);
	return(1);
}

void ft_print_mutex(t_philo *philo,char *str)
{
	//long long current_time;
	pthread_mutex_lock(&philo->data->print);
	if(philo->data->is_dead == 0)
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
	philo->eating_status = 1;
	philo->count_eat++;
	philo->last_eat_time = ft_get_time();
	usleep(philo->data->t_to_eat * 1000);
	philo->eating_status = 0;
	pthread_mutex_unlock(&philo->eat_mutex);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);

}
void ft_sleeping(t_philo *philo)
{
	philo->sleep_time = ft_get_time();
	ft_print_mutex(philo,"is sleeping");
	usleep(philo->data->t_to_sleep * 1000);
	ft_print_mutex(philo,"is thinking");
}

