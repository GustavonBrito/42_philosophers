/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gserafio <gserafio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 13:19:17 by gserafio          #+#    #+#             */
/*   Updated: 2025/08/15 13:19:19 by gserafio         ###   ########.fr       */
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
	philo->last_meal = get_timestamp();
	usleep(philo->rules->time_to_eat * 1000);
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
