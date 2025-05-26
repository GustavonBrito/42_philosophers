/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustavo-linux <gustavo-linux@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 18:54:38 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/05/25 19:04:51 by gustavo-lin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	handle_threads(t_rules *rules, t_philo *philo)
{
	int			i;
	pthread_t	thread_dead_scan;
	pthread_t	thread_must_eat_scan;

	i = -1;
	pthread_create(&thread_dead_scan, NULL, dead_scan, philo);
	pthread_create(&thread_must_eat_scan, NULL, must_eat_scan, philo);
	while (++i < rules->philo_num)
		pthread_create(&philo[i].thread, NULL, philo_routine, &philo[i]);
	i = -1;
	while (++i < rules->philo_num)
		pthread_join(philo[i].thread, NULL);
	pthread_join(thread_dead_scan, NULL);
	pthread_join(thread_must_eat_scan, NULL);
}
