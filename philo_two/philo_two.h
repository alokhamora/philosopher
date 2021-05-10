/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchaya <mchaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 14:40:53 by mchaya            #+#    #+#             */
/*   Updated: 2021/05/10 15:28:55 by mchaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TWO_H
#define PHILO_TWO_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				num;
	unsigned long	die;
	int				eat;
	int				sleep;
	int				times;
	unsigned long	t;
}				t_philo;

typedef struct s_life
{
	int				id;
	t_philo			*philo;
	sem_t			*pfork;
	unsigned long	last;
	sem_t			*death;
	sem_t			eat;
	sem_t			*text;
}				t_life;

int				ft_strlen(const char *s);
int				str_to_int(char *str);
void			init_life(t_life *life, t_philo *phil, pthread_mutex_t *death,
						  pthread_mutex_t *text);
int				free_all(t_life *life);
int				init_argv(t_philo *phil, char **argv, int argc);
unsigned long	current_time(void);
void			ft_usleep(unsigned long i);
int				exit_err(char *str);
#endif