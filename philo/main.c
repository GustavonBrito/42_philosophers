/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustavo-linux <gustavo-linux@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 22:09:34 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/05/11 23:59:19 by gustavo-lin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
	int i;
	t_rules *rules;
	t_philo *philo;

	rules = (t_rules *)malloc(sizeof(t_rules));
	if (!rules)
		return (0);
	if (init_validations(argc, argv) == -1)
	{
		free(rules);
		printf("Usage: ./philo [1-200 philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [optional: times_each_philo_must_eat]\n");
		return (0);
	}
	rules = parser(argc, argv, rules);
	philo = (t_philo *)malloc(sizeof(t_philo) * rules->philo_num);
	if (!philo)
		return (0);
	while(i < rules->philo_num)
	{
		philo[i].rules = rules;
		i++;
	}
	init_mutexes(rules);
	create_philo_threads(philo);
	rules->start_time = get_timestamp();
	think(philo);
}
