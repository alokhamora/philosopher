/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchaya <mchaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 13:28:25 by mchaya            #+#    #+#             */
/*   Updated: 2021/05/11 16:32:05 by mchaya           ###   ########.fr       */
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

/*int	free_all(t_life *life)
{
	pthread_mutex_destroy(life->text);
	pthread_mutex_destroy(life->death);
	pthread_mutex_destroy(life->pfork);
	pthread_mutex_destroy(&life->eat);
	free(life->philo);
	free(life);
	return (0);
}*/
