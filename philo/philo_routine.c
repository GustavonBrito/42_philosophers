/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustavo-linux <gustavo-linux@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 00:08:24 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/05/25 02:02:06 by gustavo-lin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (philo->rules->someone_died == 1
			|| (philo->meals == philo->rules->must_eat
				&& philo->rules->must_eat != 0))
			return (NULL);
		think(philo);
		eat(philo);
		sleep_philo(philo);
	}
	return (NULL);
}
