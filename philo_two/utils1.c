/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchaya <mchaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 13:28:25 by mchaya            #+#    #+#             */
/*   Updated: 2021/05/16 11:06:56 by mchaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (*s++ != '\0')
		i++;
	return (i);
}

void	init_life(t_life *life, t_philo *phil)
{
	sem_t	*pfork;
	sem_t	*death;
	sem_t	*text;
	int		i;

	i = 0;
	sem_unlink("death");
	sem_unlink("text");
	sem_unlink("fork");
	death = sem_open("death", O_CREAT | O_EXCL, 0664, 0);
	text = sem_open("text", O_CREAT | O_EXCL, 0664, 1);
	pfork = sem_open("fork", O_CREAT | O_EXCL, 0664, phil->num);
	while (i < phil->num)
	{
		life[i].id = i + 1;
		life[i].philo = phil;
		life[i].death = death;
		life[i].text = text;
		life[i].pfork = pfork;
		i++;
	}
}
