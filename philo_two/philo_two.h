/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchaya <mchaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 14:40:53 by mchaya            #+#    #+#             */
/*   Updated: 2021/05/12 16:45:59 by mchaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TWO_H
# define PHILO_TWO_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <semaphore.h>

typedef struct s_philo
{
	int				num;
	int 			die;
	int				eat;
	int				sleep;
	int				times;
	unsigned long	t;
}				t_philo;

typedef struct s_life
{
	int				id;
	t_philo			*philo;
	unsigned long	last;
	sem_t			*pfork;
	sem_t			*death;
	sem_t			*text;
}				t_life;

int				ft_strlen(const char *s);
int				str_to_int(char *str);
int				free_all(t_life *life);
int				init_argv(t_philo *phil, char **argv, int argc);
void			init_life(t_life *life, t_philo *phil);
unsigned long	current_time(void);
void			ft_usleep(unsigned long i);
int				exit_err(char *str);
#endif