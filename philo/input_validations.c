/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustavo-linux <gustavo-linux@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 10:33:23 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/05/05 01:36:33 by gustavo-lin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "message_validations.h"

int init_validations(int argc, char **argv)
{
	int i;
	
	i = 1;
	if (argc > 6)
		return (-1);
	// Valida numero de filosofos
	if (valid_just_numbers(argv[i]) <= 0 || ft_atol(argv[i]) > MAX_PHILO_NUMS)
		return (-1);
	i++;
	// Valida os times
	while (i < argc)
	{
		if (valid_just_numbers(argv[i]) <= 0 || ft_atol(argv[i]) == -1)
			return (-1);
		i++;
	}
	return (0);
}