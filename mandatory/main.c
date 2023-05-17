/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasserao <hasserao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 21:50:10 by hasserao          #+#    #+#             */
/*   Updated: 2023/05/17 17:03:12 by hasserao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
void ft_destroy(t_data *data)
{
	int i;
	i = -1;
	while (++i < data->num_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philo[i].eat_mutex);
		pthread_detach(data->philo[i].thread);
	}
	pthread_mutex_destroy(&data->print);
	if (data->forks != NULL)
		free(data->forks);
	if (data->philo != NULL)
		free(data->philo);
	if (data != NULL)
		free(data);
}

int ft_error_msg(t_data *data)
{
	write(2,"Error\n",6);
	if(data)
		ft_destroy(data);
	return(1);
}

int main(int argc,char **argv)
{
	t_data	*data;
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return ft_error_msg(data);
	memset(data,0,sizeof(t_data));
	if (argc < 5 || argc > 6)
		return ft_error_msg(data);
	ft_parsing(argc, argv);
	ft_init(data,argc,argv);
	if(ft_dinning(data))
		return ft_error_msg(data);
	ft_destroy(data);
	return(0);
}
