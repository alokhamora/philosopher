
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