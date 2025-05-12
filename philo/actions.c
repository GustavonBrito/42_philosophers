/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustavo-linux <gustavo-linux@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:49:01 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/05/12 00:07:28 by gustavo-lin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int eat(t_philo *philo);
// int sleep();
// int die();
int	think(t_philo *philo);

int think(t_philo *philo)
{
	printf("%ld %d: está pensando\n", get_timestamp() - philo->rules->start_time, philo->id);
	return (1);
};

int eat(t_philo *philo)
{
	struct timeval timeval;
	
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(&philo->rules->m_write);
	printf("lock");
	philo->meals++;
	philo->last_meal = gettimeofday(&timeval, NULL);
	pthread_mutex_unlock(&philo->rules->m_write);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	usleep(10);
	return (1);
}

//int sleep();

//int die();