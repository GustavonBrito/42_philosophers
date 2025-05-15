/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustavo-linux <gustavo-linux@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 22:09:34 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/05/12 22:21:56 by gustavo-lin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_rules	*rules;
	t_philo	*philo;

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
	init_mutexes(rules);
	if (init_philo(&philo, rules) == 0)
		return (free(rules), free(philo), 0);
	rules->start_time = get_timestamp();
	philo_routine();
}
