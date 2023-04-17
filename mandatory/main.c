/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasserao <hasserao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 21:50:10 by hasserao          #+#    #+#             */
/*   Updated: 2023/04/16 20:50:10 by hasserao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int main(int argc,char **argv)
{
	if (argc < 5 || argc > 6)
		printf("Error: Wrong number of arguments\n ");
	ft_parsing(argc, argv);
}
