/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustavo-linux <gustavo-linux@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 20:56:53 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/05/06 23:55:50 by gustavo-lin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//printf("Usage: ./philo [1-200 philosophers] [time_to_die] [time_to_eat] 
//[time_to_sleep] [optional: times_each_philo_must_eat]\n");

void parser(int argc, char **argv, t_rules *rules)
{
	rules->philo_num = ft_atol(argv[1]);
	rules->time_to_die = ft_atol(argv[2]);
	rules->time_to_eat = ft_atol(argv[3]);
	rules->time_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
		rules->must_eat = ft_atol(argv[5]);
}