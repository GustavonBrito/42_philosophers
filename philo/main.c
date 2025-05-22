/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustavo-linux <gustavo-linux@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 22:09:34 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/05/22 15:12:41 by gustavo-lin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_rules	*rules;
	t_philo	*philo;
	int i;
	pthread_t thread_dead_scan;
	pthread_t thread_must_eat_scan;
	
	i = -1;
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
	pthread_create(&thread_dead_scan, NULL, dead_scan, philo);
	pthread_create(&thread_must_eat_scan, NULL, must_eat_scan, philo);
	while (++i < rules->philo_num)
		pthread_create(&philo[i].thread, NULL, philo_routine, &philo[i]);
	i = -1;
	while (++i < rules->philo_num)
		pthread_join(philo[i].thread, NULL);
	pthread_join(thread_dead_scan, NULL);
	pthread_join(thread_must_eat_scan, NULL);
	if (philo->rules->someone_died == 1 || (philo->meals >= philo->rules->must_eat && philo->rules->must_eat != 0))
		return (0);
	return (0);
}
