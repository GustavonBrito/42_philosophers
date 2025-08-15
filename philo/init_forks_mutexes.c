/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_forks_mutexes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gserafio <gserafio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 13:19:30 by gserafio          #+#    #+#             */
/*   Updated: 2025/08/15 13:19:31 by gserafio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_forks_mutexes(t_rules *rules)
{
	int	i;

	i = -1;
	rules->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* rules->philo_num);
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
	return (1);
}
