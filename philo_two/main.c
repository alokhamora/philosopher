/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchaya <mchaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 14:41:32 by mchaya            #+#    #+#             */
/*   Updated: 2021/05/10 17:34:26 by mchaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

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
	t_philo	*phil;

	phil = malloc(sizeof(t_philo));
	if (init_argv(phil, argv, argc) < 0)
		return (exit_err("Error: wrong argument"));
	phil->t = current_time();
	life = malloc(sizeof(t_life) * phil->num);

	return (0);
}
