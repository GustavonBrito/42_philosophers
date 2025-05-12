/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philo_thread.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustavo-linux <gustavo-linux@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 23:48:37 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/05/12 00:11:03 by gustavo-lin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int create_threads(t_rules *rules, t_philo *philo)
{
	int i;

	i = -1;
	while (++i < rules->philo_num)
		pthread_create(&philo[i].thread, NULL, think, &philo[i]);
	return (1);
}