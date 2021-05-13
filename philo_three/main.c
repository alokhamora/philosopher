/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchaya <mchaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 18:19:38 by mchaya            #+#    #+#             */
/*   Updated: 2021/05/12 18:59:56 by mchaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int	main(int argc, char **argv)
{
	t_philo	*phil;
	t_life	*life;

	phil = malloc(sizeof(t_philo));
	if (init_argv(phil, argv, argc) < 0)
		return (exit_err("Error: wrong argument\n"));
	phil->t = current_time();
	life = malloc(sizeof(t_life) * phil->num);

}