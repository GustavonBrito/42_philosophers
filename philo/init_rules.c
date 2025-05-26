/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_rules.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustavo-linux <gustavo-linux@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 21:14:02 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/05/25 21:34:38 by gustavo-lin      ###   ########.fr       */
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
