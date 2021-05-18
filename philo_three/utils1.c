/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchaya <mchaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 11:22:18 by mchaya            #+#    #+#             */
/*   Updated: 2021/05/18 16:49:28 by mchaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

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
	while (i < life->philo->num)
		kill(life[i++].pid, 9);
	sem_unlink("text");
	sem_unlink("fork");
	free(life->philo);
	free(life);
	return (0);
}

void	init_life(t_life *life, t_philo *phil)
{
	sem_t	*pfork;
	sem_t	*text;
	int		i;

	i = 0;
	sem_unlink("text");
	sem_unlink("fork");
	text = sem_open("text", O_CREAT | O_EXCL, 0664, 1);
	pfork = sem_open("fork", O_CREAT | O_EXCL, 0664, phil->num);
	while (i < phil->num)
	{
		life[i].id = i + 1;
		life[i].philo = phil;
		life[i].text = text;
		life[i].pfork = pfork;
		i++;
	}
}
