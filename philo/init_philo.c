/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gserafio <gserafio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 13:19:36 by gserafio          #+#    #+#             */
/*   Updated: 2025/08/15 13:19:38 by gserafio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philo(t_philo **philo, t_rules *rules)
{
	int	i;

	i = -1;
	*philo = (t_philo *)malloc(sizeof(t_philo) * rules->philo_num);
	if (!(*philo))
		return (-1);
	while (++i < rules->philo_num)
	{
		(*philo)[i].id = i + 1;
		(*philo)[i].rules = rules;
		(*philo)[i].left_fork = &rules->forks[i];
		(*philo)[i].right_fork = &rules->forks[(i + 1) % rules->philo_num];
		(*philo)[i].last_meal = get_timestamp();
		(*philo)[i].finished_eating = 0;
		(*philo)[i].meals = 0;
	}
	return (1);
}
