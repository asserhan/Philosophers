/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasserao <hasserao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 22:38:16 by hasserao          #+#    #+#             */
/*   Updated: 2023/04/16 17:46:44 by hasserao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long	ft_atoi(char *str)
{
	int		i;
	long	res;

	i = 0;
	res = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '-')
		return(-1);
	if (str[i] == '+')
		i++;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		res *= 10;
		res += str[i] - '0';
		i++;
	}
	if (str[i])
		return(-1);
	return (res);
}
void ft_parsing(int argc,char **argv)
{
	int i;

	i = 0;
	while(++i < argc)
	{
		if(ft_atoi(argv[i]) == -1)
		{
			printf("Error : Wrong argument\n");
			exit(1);
		}
	}
}
