/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasserao <hasserao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 01:30:16 by hasserao          #+#    #+#             */
/*   Updated: 2023/05/17 23:13:10 by hasserao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void ft_init_forks(t_data *data)
{
	int i;
	i = -1;
	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)*data->num_philo);
	if(!data->forks)
		ft_error_msg(data);
	while (++i < data->num_philo)
	{
		if(pthread_mutex_init(&data->forks[i], NULL))
			ft_error_msg(data);
	}
}

void ft_init_philo(t_data *data)
{
	int i;
	i = -1;
	data->philo = (t_philo *)malloc(sizeof(t_philo)*data->num_philo);
	if(!data->philo)
		ft_error_msg(data);
	while(++i < data->num_philo)
	{
		data->philo[i].id = i + 1;
		data->philo[i].right_fork = &data->forks[i];
		data->philo[i].left_fork = &data->forks[(i + 1) % data->num_philo];
		data->philo[i].last_eat_time = ft_get_time();
		data->philo[i].meals_eaten = 0;
		data->philo[i].data = data;
		if(pthread_mutex_init(&data->philo[i].eat_mutex, NULL))
			ft_error_msg(data);
		//data->philo[i].eat_time = 0;
	}

}
void ft_init(t_data *data,int argc,char **argv)
{
	data->num_philo = ft_atoi(argv[1]);
	data->t_to_die = ft_atoi(argv[2]);
	data->t_to_eat = ft_atoi(argv[3]);
	data->t_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->num_eat = ft_atoi(argv[5]);
	else
		data->num_eat = -1;

	if (data->num_philo < 1 || data->num_philo > 200 || data->t_to_die < 60 || data->t_to_eat < 60 || data->t_to_sleep < 60)
		ft_error_msg(data);
	if(pthread_mutex_init(&data->print, NULL))
		ft_error_msg(data);
	data->is_dead = 0;
	data->eaten_philos = 0;
	//pthread_mutex_init(&data->philo->eat_mutex, NULL);
	ft_init_forks(data);
	ft_init_philo(data);
}
