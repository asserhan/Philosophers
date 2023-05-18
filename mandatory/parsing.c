/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasserao <hasserao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 22:38:16 by hasserao          #+#    #+#             */
/*   Updated: 2023/05/18 17:55:08 by hasserao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int ft_is_space(char c)
{
	return (c == ' ' || c == '\t' || (c >=9 && c <= 13));
}

long	ft_atoi(char *str)
{
	int		i;
	long	res;

	i = 0;
	res = 0;
	while (ft_is_space(str[i]))
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
	if(res > INT_MAX)
		return(-1);
	return (res);
}
int ft_parsing(int argc,char **argv)
{
	int i;

	i = 0;
	while(++i < argc)
	{
		if(ft_atoi(argv[i]) == -1)
			return(1);
	}
	return(0);
}
