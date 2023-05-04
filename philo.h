/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasserao <hasserao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 21:50:25 by hasserao          #+#    #+#             */
/*   Updated: 2023/04/28 19:01:48 by hasserao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <string.h>

typedef struct s_data
{
	int num_philo;
	int t_to_die;
	int t_to_eat;
	int t_to_sleep;
	int num_eat;
	int start_time;
	int is_dead;
	pthread_mutex_t *forks;
	pthread_mutex_t *print;
	pthread_mutex_t lock;
}		t_data;
typedef struct s_philo
{
	pthread_t thread;
	int		id;
	t_data	*data;

}			t_philo;
void ft_parsing(int argc,char **argv);
#endif
