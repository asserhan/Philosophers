/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasserao <hasserao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 21:50:25 by hasserao          #+#    #+#             */
/*   Updated: 2023/05/16 22:57:10 by hasserao         ###   ########.fr       */
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
# include <sys/time.h>


typedef struct s_data
{
	int num_philo;
	int t_to_die;
	int t_to_eat;
	int t_to_sleep;
	int num_eat;
	int eaten_philos;
	int game_over;
	long long start_time;
	int is_dead;
	pthread_mutex_t *forks;
	pthread_mutex_t print;
	struct s_philo  *philo;

}		t_data;

typedef struct s_philo
{
	pthread_t thread;
	int		id;
	//int		is_dead;
	int		count_eat;
	//int		eat_time;
	int		eating_status;
	long long last_eat_time;
	long long sleep_time;

	t_data	*data;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t *left_fork;
	pthread_mutex_t eat_mutex;

}			t_philo;
long	ft_atoi(char *str);
void ft_parsing(int argc,char **argv);
int ft_error_msg(t_data *data);
void ft_init(t_data *data,int argc,char **argv);
long long  ft_get_time();
void ft_print_mutex(t_philo *philo,char *str);
void ft_eating(t_philo *philo);
void ft_sleeping(t_philo *philo);
int ft_dinning(t_data *data);

#endif
