/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasserao <hasserao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 01:30:16 by hasserao          #+#    #+#             */
/*   Updated: 2023/04/28 19:01:21 by hasserao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void ft_init(t_data *data,int argc,char **argv)
{
	data->is_dead = 0;
	data->num_philo = ft_atoi(argv[1]);
	data->t_to_die = ft_atoi(argv[2]);
	data->t_to_eat = ft_atoi(argv[3]);
	data->t_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->num_eat = ft_atoi(argv[5]);
	else
		data->num_eat = -1;
	if (data->num_philo < 1 || data->num_philo > 200 || data->t_to_die < 60 || data->t_to_eat < 60 || data->t_to_sleep < 60)
		ft_error_msg();
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->lock, NULL);
}
