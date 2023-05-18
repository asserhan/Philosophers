/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasserao <hasserao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 21:50:10 by hasserao          #+#    #+#             */
/*   Updated: 2023/05/18 18:04:04 by hasserao         ###   ########.fr       */
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
void tt(void)
{
	system("leaks philo");
}
int main(int argc,char **argv)
{
	//atexit(tt);
	t_data	*data;
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return(ft_error_msg(data));
	memset(data,0,sizeof(t_data));
	if (argc < 5 || argc > 6)
		return(ft_error_msg(data));
	if(ft_parsing(argc, argv))
		return(ft_error_msg(data));
	if(ft_init(data,argc,argv))
		return(ft_error_msg(data));
	if(ft_init_forks(data))
		return(ft_error_msg(data));
	if(ft_init_philo(data))
		return(ft_error_msg(data));
	if(ft_dinning(data))
		return(ft_error_msg(data));
	ft_destroy(data);
	system("leaks philo");
	return(0);
}
