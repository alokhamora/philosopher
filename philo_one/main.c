/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchaya <mchaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 11:09:12 by mchaya            #+#    #+#             */
/*   Updated: 2021/05/18 14:12:30 by mchaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	*check_death(void *tmp)
{
	t_life	*life;

	life = tmp;
	while (1)
	{
		usleep(100);
		pthread_mutex_lock(&life->eat);
		if (current_time() - life->last >= life->philo->die)
		{
			pthread_mutex_lock(life->text);
			printf("%ld %d died\n", current_time() - life->philo->t, life->id);
			pthread_mutex_unlock(life->death);
			break ;
		}
		pthread_mutex_unlock(&life->eat);
	}
	return (NULL);
}

void	philo_eat(t_life *tmp)
{
	if (tmp->id == tmp->philo->num)
		pthread_mutex_lock(&tmp->pfork[0]);
	else
		pthread_mutex_lock(&tmp->pfork[tmp->id]);
	pthread_mutex_lock(tmp->text);
	printf("%lu %d has taken a fork\n", current_time() - tmp->philo->t,
		   tmp->id);
	pthread_mutex_unlock(tmp->text);
	pthread_mutex_lock(&tmp->pfork[tmp->id - 1]);
	pthread_mutex_lock(tmp->text);
	printf("%lu %d has taken a fork\n", current_time() - tmp->philo->t,
		   tmp->id);
	pthread_mutex_unlock(tmp->text);
	pthread_mutex_lock(&tmp->eat);
	tmp->last = current_time();
	pthread_mutex_lock(tmp->text);
	printf("%ld %d is eating\n", current_time() - tmp->philo->t, tmp->id);
	pthread_mutex_unlock(tmp->text);
	ft_usleep(tmp->philo->eat);
	pthread_mutex_unlock(&tmp->eat);
	if (tmp->id == tmp->philo->num)
		pthread_mutex_unlock(&tmp->pfork[0]);
	else
		pthread_mutex_unlock(&tmp->pfork[tmp->id]);
	pthread_mutex_unlock(&tmp->pfork[tmp->id - 1]);
}

void	*life_philo(void *life)
{
	t_life		*tmp;
	pthread_t	pthread;
	int			k;

	k = 0;
	tmp = life;
	tmp->last = tmp->philo->t;
	pthread_create(&pthread, NULL, check_death, tmp);
	if (tmp->id % 2 == 0)
		ft_usleep(10);
	while (1)
	{
		philo_eat(tmp);
		if (tmp->philo->times != -1)
			k++;
		if (tmp->philo->times != -1 && k == tmp->philo->times)
			unlock_death(tmp);
		pthread_mutex_lock(tmp->text);
		printf("%ld %d is sleeping\n", current_time() - tmp->philo->t, tmp->id);
		pthread_mutex_unlock(tmp->text);
		ft_usleep(tmp->philo->sleep);
		pthread_mutex_lock(tmp->text);
		printf("%ld %d is thinking\n", current_time() - tmp->philo->t, tmp->id);
		pthread_mutex_unlock(tmp->text);
	}
}

void	exec_philo(t_life *life)
{
	int			i;
	int			k;
	pthread_t	thread;

	i = 0;
	k = life->philo->num;
	while (i < k)
	{
		pthread_create(&thread, NULL, (void *)life_philo, life + i);
		pthread_detach(thread);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_philo			*phil;
	pthread_mutex_t	*death;
	pthread_mutex_t	*text;
	t_life			*life;
	int				k;

	k = 0;
	phil = malloc(sizeof(t_philo));
	if (init_argv(phil, argv, argc) < 0)
		return (exit_err("Error: wrong argument\n"));
	phil->t = current_time();
	life = malloc(sizeof(t_life) * phil->num);
	death = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(death, NULL);
	pthread_mutex_lock(death);
	text = malloc(sizeof (pthread_mutex_t));
	pthread_mutex_init(text, NULL);
	life->check = &k;
	init_life(life, phil, death, text);
	exec_philo(life);
	pthread_mutex_lock(death);
	return (free_all(life));
}
