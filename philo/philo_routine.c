/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gserafio <gserafio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 13:19:57 by gserafio          #+#    #+#             */
/*   Updated: 2025/08/15 13:19:59 by gserafio         ###   ########.fr       */
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
