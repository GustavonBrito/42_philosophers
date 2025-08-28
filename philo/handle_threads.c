/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustavo <gustavo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 13:19:24 by gserafio          #+#    #+#             */
/*   Updated: 2025/08/27 23:41:23 by gustavo          ###   ########.fr       */
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
	if (rules->must_eat != 0 && rules->philo_num > 1)
		pthread_create(&thread_must_eat_scan, NULL, must_eat_scan, philo);
	while (++i < rules->philo_num)
		pthread_create(&philo[i].thread, NULL, philo_routine, &philo[i]);
	i = -1;
	while (++i < rules->philo_num)
		pthread_join(philo[i].thread, NULL);
	pthread_join(thread_dead_scan, NULL);
	if (rules->must_eat != 0)
		pthread_join(thread_must_eat_scan, NULL);
}
