/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchaya <mchaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 13:28:25 by mchaya            #+#    #+#             */
/*   Updated: 2021/05/16 15:09:50 by mchaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (*s++ != '\0')
		i++;
	return (i);
}

int	free_all(t_life *life)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(life->death);
	pthread_mutex_destroy(life->text);
	pthread_mutex_destroy(life->pfork);
	while (i < life->philo->num)
	{
		pthread_mutex_destroy(&(life[i]).eat);
		i++;
	}
	free(life->philo);
	free(life);
	return (0);
}

void	unlock_death(t_life *tmp)
{
	*(tmp->check) = *(tmp->check) + 1;
	if (*tmp->check == tmp->philo->num)
		pthread_mutex_unlock(tmp->death);
}

void	init_life(t_life *life, t_philo *phil, pthread_mutex_t *death,
				  pthread_mutex_t *text)
{
	int				i;
	pthread_mutex_t	*p_fork;

	i = 0;
	p_fork = malloc(sizeof(pthread_mutex_t) * phil->num);
	while (i < phil->num)
	{
		pthread_mutex_init(p_fork + i, NULL);
		life[i].id = i + 1;
		life[i].philo = phil;
		life[i].pfork = p_fork;
		life[i].death = death;
		life[i].text = text;
		life[i].check = life[0].check;
		pthread_mutex_init(&life[i].eat, NULL);
		i++;
	}
}
