/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustavo-linux <gustavo-linux@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 22:09:34 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/05/25 18:58:29 by gustavo-lin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_rules		*rules;
	t_philo		*philo;

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
	if (philo->rules->someone_died == 1 \
	|| (philo->meals >= philo->rules->must_eat \
	&& philo->rules->must_eat != 0))
		return (free(rules->forks), free(philo), free(rules), 0);
}
