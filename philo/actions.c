/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustavo-linux <gustavo-linux@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:49:01 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/05/22 11:12:25 by gustavo-lin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	die(t_philo philo);
void	eat(t_philo *philo);
void	sleep_philo(t_philo *philo);
void	think(t_philo *philo);
void	*dead_scan(void *arg);

void think(t_philo *philo)
{
	pthread_mutex_lock(&philo->rules->m_write);
	printf("%ld %d is thinking\n", get_timestamp() - philo->rules->start_time, philo->id);
	pthread_mutex_unlock(&philo->rules->m_write);
};

void eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(&philo->rules->m_write);
		printf("%ld %d has taken a fork\n", get_timestamp() - philo->rules->start_time, philo->id);
		pthread_mutex_unlock(&philo->rules->m_write);
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(&philo->rules->m_write);
		printf("%ld %d has taken a fork\n", get_timestamp() - philo->rules->start_time, philo->id);
		pthread_mutex_unlock(&philo->rules->m_write);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(&philo->rules->m_write);
		printf("%ld %d has taken a fork\n", get_timestamp() - philo->rules->start_time, philo->id);
		pthread_mutex_unlock(&philo->rules->m_write);
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(&philo->rules->m_write);
		printf("%ld %d has taken a fork\n", get_timestamp() - philo->rules->start_time, philo->id);
		pthread_mutex_unlock(&philo->rules->m_write);
	}
	pthread_mutex_lock(&philo->rules->m_write);
	printf("%ld %d is eating\n", get_timestamp() - philo->rules->start_time, philo->id);
	pthread_mutex_unlock(&philo->rules->m_write);
	usleep(philo->rules->time_to_eat * 1000);
	philo->last_meal = get_timestamp();
	philo->meals++;
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void sleep_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->rules->m_write);
	printf("%ld %d is sleeping\n", get_timestamp() - philo->rules->start_time, philo->id);
	pthread_mutex_unlock(&philo->rules->m_write);
	usleep(philo->rules->time_to_sleep * 1000);
}

void die(t_philo philo)
{	
	pthread_mutex_lock(&philo.rules->m_write);
	printf("%ld %d died\n", get_timestamp() - philo.rules->start_time, philo.id);
	pthread_mutex_unlock(&philo.rules->m_write);
	pthread_mutex_lock(&philo.rules->dead_philo);
	philo.rules->someone_died = 1;
	pthread_mutex_unlock(&philo.rules->dead_philo);
}

void *dead_scan(void *arg)
{
	int i;
	t_philo *philo = (t_philo *)arg;
	t_rules *rules = philo[0].rules;
	i = 0;
	while (1)
	{
		if (rules->someone_died)
			return NULL;
		if (i >= rules->philo_num)
			i = 0;
		if ((get_timestamp() - philo[i].last_meal) > rules->time_to_die && philo[i].last_meal != 0)
			return (die(philo[i]), NULL);
		i++;
		usleep(1000);
	}
	return (NULL);
}
