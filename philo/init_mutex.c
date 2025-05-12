/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mutex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustavo-linux <gustavo-linux@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 09:10:32 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/05/11 23:37:19 by gustavo-lin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int init_mutexes(t_rules *rules)
{
	int i;

	i = -1;
	rules->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * rules->philo_num);
	if (!rules->forks)
		return (0);
	while (++i < rules->philo_num)
	{
		if (pthread_mutex_init(&rules->forks[i], NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&rules->forks[i]);
			free(rules->forks);
			return (-1);
		}
	}
	return(1);
}
