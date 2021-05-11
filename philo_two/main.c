/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchaya <mchaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 14:41:32 by mchaya            #+#    #+#             */
/*   Updated: 2021/05/11 18:15:44 by mchaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	*check_death(void *tmp)
{
	t_life	*life;

	life = tmp;
	while (1)
	{
		usleep(100);
		sem_wait(life->eat);
		if (current_time() - life->last >= life->philo->die)
		{
			sem_wait(life->text);
			printf("%ld %d died\n", current_time() - life->philo->t, life->id);
			sem_post(life->death);
			break ;
		}
		sem_post(life->eat);
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
	sem_wait(tmp->eat);
	tmp->last = current_time();
	sem_wait(tmp->text);
	printf("%ld %d is eating\n", current_time() - tmp->philo->t, tmp->id);
	sem_post(tmp->text);
	ft_usleep(tmp->philo->eat);
	sem_post(tmp->eat);
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
	pthread_create(&pthread, NULL, check_death, tmp);
	if (tmp->id % 2 == 0)
		ft_usleep(10);
	while (1)
	{
		if (tmp->philo->times != -1 && k == tmp->philo->times)
			sem_post(tmp->death);
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
	int		i;
	sem_t	*pfork;
	sem_t	*death;
	sem_t	*eat;
	sem_t	*text;

	i = 0;
	phil = malloc(sizeof(t_philo));
	if (init_argv(phil, argv, argc) < 0)
		return (exit_err("Error: wrong argument\n"));
	phil->t = current_time();
	life = malloc(sizeof(t_life) * phil->num);
	death = sem_open("death", O_CREAT, 0664, 0);
	text = sem_open("text", O_CREAT, 0664, 1);
	eat = sem_open("eat", O_CREAT, 0664, phil->num);
	pfork = sem_open("fork", O_CREAT, 0664, phil->num);
	while (i < phil->num)
	{
		life[i].id = i + 1;
		life[i].philo = phil;
		life[i].death = death;
		life[i].text = text;
		life[i].eat = eat;
		life[i].pfork = pfork;
		i++;
	}
	exec_philo(life);
	sem_wait(life->death);
	return (0);
}
