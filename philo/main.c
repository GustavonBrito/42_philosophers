/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustavo-linux <gustavo-linux@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 22:09:34 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/05/06 23:58:16 by gustavo-lin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
	t_rules *rules;

	rules = (t_rules *)malloc(sizeof(t_rules));
	if (!rules)
		return (0);
	if (init_validations(argc, argv) == -1)
	{
		free(rules);
		printf("Usage: ./philo [1-200 philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [optional: times_each_philo_must_eat]\n");
		return (0);
	}
	parser(argc, argv, rules);
	
}