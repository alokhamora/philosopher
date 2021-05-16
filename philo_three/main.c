/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchaya <mchaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 18:19:38 by mchaya            #+#    #+#             */
/*   Updated: 2021/05/16 12:08:51 by mchaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	*check_death(void *tmp)
{
	t_life	*life;

	life = tmp;
	while (1)
	{
		usleep(1000);
		if (current_time() - life->last >= (unsigned int)life->philo->die)
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

void	life_philo(t_life *tmp)
{
	pthread_t	pthread;
	int			k;

	k = 0;
	tmp->last = tmp->philo->t;
	pthread_create(&pthread, NULL, check_death, tmp);
	if (tmp->id % 2 == 0)
		ft_usleep(10);
	while (1)
	{
		if (tmp->philo->times != -1 && k == tmp->philo->times)
		{
			sem_post(tmp->death);
			exit();
		}
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

	i = 0;
	k = life->philo->num;
	while (i < k)
	{
		life[i].pid = fork();
		if (life[i].pid == 0)
			life_philo(&life[i]);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_philo	*phil;
	t_life	*life;
	int i;

	i = 0;
	phil = malloc(sizeof(t_philo));
	if (init_argv(phil, argv, argc) < 0)
		return (exit_err("Error: wrong argument\n"));
	phil->t = current_time();
	life = malloc(sizeof(t_life) * phil->num);
	init_life(life, phil);
	exec_philo(life);
	sem_wait(life->death);
	while (i < phil->num)
	{
		kill(life[i].pid, 9);
		i++;
	}
	free(phil);
	free(life);
	return (0);
}