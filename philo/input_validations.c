/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustavo-linux <gustavo-linux@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 10:33:23 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/05/25 18:43:01 by gustavo-lin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_error_message(void)
{
	printf("Usage: ./philo [1-200 philosophers] \
[time_to_die] [time_to_eat] [time_to_sleep] \
[optional: times_each_philo_must_eat] \
\nAll values must be positive\n");
}

int	init_validations(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc != 6 && argc != 5)
		return (print_error_message(), -1);
	if (valid_just_numbers(argv[i]) <= 0 || ft_atol(argv[i]) > 200)
		return (print_error_message(), -1);
	i++;
	while (i < argc)
	{
		if (valid_just_numbers(argv[i]) <= 0 || ft_atol(argv[i]) == -1)
			return (print_error_message(), -1);
		i++;
	}
	return (0);
}
