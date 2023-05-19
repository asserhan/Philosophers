/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasserao <hasserao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 21:50:25 by hasserao          #+#    #+#             */
/*   Updated: 2023/05/19 04:05:52 by hasserao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data
{
	int				num_philo;
	int				t_to_die;
	int				t_to_eat;
	int				t_to_sleep;
	int				num_eat;
	long long		start_time;
	pthread_mutex_t	start_time_mutex;
	int				is_dead;
	pthread_mutex_t	is_dead_mutex;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	struct s_philo	*philo;

}					t_data;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	long long		last_eat_time;
	pthread_mutex_t	last_eat_time_mutex;
	int				meals_eaten;
	pthread_mutex_t	meals_eaten_mutex;
	t_data			*data;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;

}					t_philo;

long				ft_atoi(char *str);
void				ft_read_args(t_data *data, char **argv);
int					ft_parsing(int argc, char **argv);
int					ft_error_msg(t_data *data);
long long			ft_get_time(void);
int					ft_mutex_lock(pthread_mutex_t *mutex, t_data *data);
int					ft_mutex_unlock(pthread_mutex_t *mutex, t_data *data);
int					ft_mutex_destroy(pthread_mutex_t *mutex, t_data *data);
int					ft_mutex_init(pthread_mutex_t *mutex, t_data *data);
int					ft_mutex_detach(pthread_t thread, t_data *data);
int					ft_init_forks(t_data *data);
int					ft_init_philo(t_data *data);
int					ft_init(t_data *data, int argc, char **argv);
long long			ft_get_time(void);
void				ft_print_mutex(t_philo *philo, char *str);
int					one_philo(t_philo *philo);
void				ft_check_meals(t_philo *philo, int i, int done);

void				ft_eating(t_philo *philo);
void				ft_sleeping(t_philo *philo);
int					ft_meals(t_philo *philo);
int					the_routine(t_data *data);
int					supervisor(t_data *data);
int					ft_dinning(t_data *data);
int					all_philos_eaten(t_philo *philo);
void				*ft_routine_2(void *arg);

#endif
