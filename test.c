/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasserao <hasserao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 21:54:45 by hasserao          #+#    #+#             */
/*   Updated: 2023/04/13 22:00:11 by hasserao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

int				m = 0;
pthread_mutex_t	mutex;
void	*start_routine(void)
{
	for (int i = 0; i < 1000000; i++)
	{
		pthread_mutex_lock(&mutex);
		m++;
		pthread_mutex_unlock(&mutex);
	}
	//printf("%d\n",m);
}

int	main(void)
{
	pthread_t t1, t2;
	pthread_mutex_init(&mutex, NULL);
	if (pthread_create(&t1, NULL, &start_routine, NULL) != 0)
		return (1);
	if (pthread_create(&t2, NULL, &start_routine, NULL))
		return (1);
	if (pthread_join(t1, NULL))
		return (2);
	if (pthread_join(t2, NULL) != 0)
		return (2);
	pthread_mutex_destroy(&mutex);
	printf("%d\n", m);
	return (0);
}
