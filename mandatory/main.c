/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasserao <hasserao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 21:50:10 by hasserao          #+#    #+#             */
/*   Updated: 2023/04/23 19:11:41 by hasserao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
void ft_error_msg(void)
{
	write(2,"Error\n",6);
	exit(1);
}
int main(int argc,char **argv)
{
	t_philo	*philo;
	t_data	*data;
	if (argc < 5 || argc > 6)
		ft_error_msg();
	ft_parsing(argc, argv);
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		ft_error_msg();
	memset(data,0,sizeof(t_data));
}
