/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchaya <mchaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 14:41:32 by mchaya            #+#    #+#             */
/*   Updated: 2021/05/18 14:38:03 by mchaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	*check_death(void *tmp)
{
	t_life	*life;

	life = tmp;
	while (1)
	{
		usleep(1000);
		if (current_time() - life->last >= life->philo->die)
		{
			sem_wait(life->text);
			printf("%ld %d died\n", current_time() - life->philo->t, life->id);
			sem_post(life->death);
			break ;
		}
	}
	return (NULL);
}

void	philo_eat(t_life *tmp)
{
	sem_wait(tmp->pfork);
	sem_wait(tmp->text);
	printf("%lu %d has taken a fork\n", current_time() - tmp->philo->t,
		   tmp->id);
	sem_post(tmp->text);
	sem_wait(tmp->pfork);
	sem_wait(tmp->text);
	printf("%lu %d has taken a fork\n", current_time() - tmp->philo->t,
		   tmp->id);
	sem_post(tmp->text);
	tmp->last = current_time();
	sem_wait(tmp->text);
	printf("%ld %d is eating\n", current_time() - tmp->philo->t, tmp->id);
	sem_post(tmp->text);
	ft_usleep(tmp->philo->eat);
	sem_post(tmp->pfork);
	sem_post(tmp->pfork);
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
		if (tmp->philo->times != -1 && k == tmp->philo->times)
			unlock_death(tmp);
		if (tmp->philo->times != -1)
			k++;
		philo_eat(tmp);
		sem_wait(tmp->text);
		printf("%ld %d is sleeping\n", current_time() - tmp->philo->t, tmp->id);
		sem_post(tmp->text);
		ft_usleep(tmp->philo->sleep);
		sem_wait(tmp->text);
		printf("%ld %d is thinking\n", current_time() - tmp->philo->t, tmp->id);
		sem_post(tmp->text);
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
	t_philo	*phil;
	t_life	*life;
	int		k;

	k = 0;
	phil = malloc(sizeof(t_philo));
	if (init_argv(phil, argv, argc) < 0)
		return (exit_err("Error: wrong argument\n"));
	phil->t = current_time();
	life = malloc(sizeof(t_life) * phil->num);
	life->check = &k;
	init_life(life, phil);
	exec_philo(life);
	sem_wait(life->death);
	sem_unlink("death");
	sem_unlink("text");
	sem_unlink("fork");
	free(phil);
	free(life);
	return (0);
}
