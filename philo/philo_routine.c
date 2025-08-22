/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 13:19:57 by gserafio          #+#    #+#             */
/*   Updated: 2025/08/22 10:56:46 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&philo->rules->dead_philo);
		if (philo->rules->someone_died == 1
			|| (philo->meals == philo->rules->must_eat
				&& philo->rules->must_eat != 0))
		{
			pthread_mutex_unlock(&philo->rules->dead_philo);
			return (NULL);
		}
		else
			pthread_mutex_unlock(&philo->rules->dead_philo);
		think(philo);
		eat(philo);
		sleep_philo(philo);
	}
	return (NULL);
}
