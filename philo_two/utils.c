/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchaya <mchaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 17:29:41 by mchaya            #+#    #+#             */
/*   Updated: 2021/05/10 14:52:42 by mchaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int	str_to_int(char *str)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (-1);
		k = k * 10 + str[i] - '0';
		if (k < 0)
			return (-1);
		i++;
	}
	return (k);
}

int	init_argv(t_philo *phil, char **argv, int argc)
{
	if (argc != 5 && argc != 6)
		return (-1);
	if (argc != 6)
		phil->times = -1;
	else
		phil->times = str_to_int(argv[5]);
	phil->num = str_to_int(argv[1]);
	phil->die = (unsigned long)str_to_int(argv[2]);
	phil->eat = str_to_int(argv[3]);
	phil->sleep = str_to_int(argv[4]);
	if (phil->num < 2 || phil->sleep <= 0 || phil->eat <= 0 || phil->die
		<= 0 || (argc == 6 && phil->times <= 0))
		return (-1);
	return (1);
}

unsigned long	current_time(void)
{
	struct timeval	tp;

	gettimeofday(&tp, NULL);
	return (tp.tv_sec * 1000 + tp.tv_usec / 1000);
}

void	ft_usleep(unsigned long i)
{
	unsigned long	t;

	t = current_time();
	while (current_time() <= t + i)
		usleep(500);
}

int	exit_err(char *str)
{
	write(2, str, ft_strlen(str));
	return (0);
}
