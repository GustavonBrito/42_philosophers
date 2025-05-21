/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philo_thread.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustavo-linux <gustavo-linux@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 23:48:37 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/05/18 18:58:42 by gustavo-lin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int init_philo(t_philo **philo, t_rules *rules)
{
	int i;

	i = -1;
	*philo = (t_philo *)malloc(sizeof(t_philo) * rules->philo_num);
	if (!(*philo))
		return (0);
	while(++i < rules->philo_num)
	{
		(*philo)[i].id = i + 1;
		(*philo)[i].rules = rules;
		(*philo)[i].left_fork = &rules->forks[i];
		(*philo)[i].right_fork = &rules->forks[(i + 1) % rules->philo_num];
		(*philo)[i].last_meal = 0;
	}
	return (1);
}