/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_rules.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gserafio <gserafio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 13:19:42 by gserafio          #+#    #+#             */
/*   Updated: 2025/08/15 13:19:43 by gserafio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_rules	*init_rules(int argc, char **argv, t_rules *rules)
{
	rules->philo_num = ft_atol(argv[1]);
	rules->time_to_die = ft_atol(argv[2]);
	rules->time_to_eat = ft_atol(argv[3]);
	rules->time_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
		rules->must_eat = ft_atol(argv[5]);
	else
		rules->must_eat = 0;
	rules->someone_died = 0;
	rules->start_time = 0;
	rules->scan_end = 0;
	init_forks_mutexes(rules);
	pthread_mutex_init(&rules->m_write, NULL);
	pthread_mutex_init(&rules->dead_philo, NULL);
	return (rules);
}
