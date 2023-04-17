/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasserao <hasserao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 21:50:25 by hasserao          #+#    #+#             */
/*   Updated: 2023/04/17 01:29:33 by hasserao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_data
{
	int num_philo;
	int t_to_die;
	int t_to_eat;
	int t_to_sleep;
	int num_eat;
	int start_time;
}		t_data;
typedef struct s_philo
{
	pthread_t thread;
	int		id;
	pthread_mutex_t lock;
	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;
	pthread_mutex_t *print;
	t_data	*data;

}			t_philo;
void ft_parsing(int argc,char **argv);
#endif
