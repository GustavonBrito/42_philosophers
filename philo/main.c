/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustavo <gustavo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 13:19:53 by gserafio          #+#    #+#             */
/*   Updated: 2025/08/28 13:26:23 by gustavo          ###   ########.fr       */
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
		return (free(rules), 0);
	rules = init_rules(argc, argv, rules);
	if (init_philo(&philo, rules) == -1)
		return (free(rules), free(philo), 0);
	rules->start_time = get_timestamp();
	handle_threads(rules, philo);
	if (philo->rules->someone_died == 1
		|| (philo->meals >= philo->rules->must_eat
			&& philo->rules->must_eat != 0))
		return (free(rules->forks), free(philo), free(rules), 0);
}
