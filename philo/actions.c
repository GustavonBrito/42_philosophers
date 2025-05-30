/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustavo-linux <gustavo-linux@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:49:01 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/05/25 19:15:52 by gustavo-lin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	die(t_philo philo);
void	eat(t_philo *philo);
void	sleep_philo(t_philo *philo);
void	think(t_philo *philo);

void	think(t_philo *philo)
{
	pthread_mutex_lock(&philo->rules->m_write);
	if (philo->rules->someone_died != 1)
		printf("%ld %d is thinking\n", get_timestamp()
			- philo->rules->start_time, philo->id);
	pthread_mutex_unlock(&philo->rules->m_write);
}

void	eat(t_philo *philo)
{
	if (philo->rules->must_eat != 0 && philo->rules->must_eat <= philo->meals)
		return ;
	handle_forks(philo);
	pthread_mutex_lock(&philo->rules->m_write);
	if (philo->rules->someone_died != 1)
		printf("%ld %d is eating\n", get_timestamp() - philo->rules->start_time,
			philo->id);
	pthread_mutex_unlock(&philo->rules->m_write);
	usleep(philo->rules->time_to_eat * 1000);
	philo->last_meal = get_timestamp();
	philo->meals++;
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	sleep_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->rules->m_write);
	if (philo->rules->someone_died != 1)
		printf("%ld %d is sleeping\n", get_timestamp()
			- philo->rules->start_time, philo->id);
	pthread_mutex_unlock(&philo->rules->m_write);
	usleep(philo->rules->time_to_sleep * 1000);
}

void	die(t_philo philo)
{
	pthread_mutex_lock(&philo.rules->m_write);
	printf("%ld %d died\n", get_timestamp() - philo.rules->start_time,
		philo.id);
	pthread_mutex_unlock(&philo.rules->m_write);
	pthread_mutex_lock(&philo.rules->dead_philo);
	philo.rules->someone_died = 1;
	pthread_mutex_unlock(&philo.rules->dead_philo);
}
