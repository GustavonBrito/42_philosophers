/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_validations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gserafio <gserafio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 13:20:17 by gserafio          #+#    #+#             */
/*   Updated: 2025/08/15 13:20:18 by gserafio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atol(const char *nptr)
{
	int		index;
	int		sign;
	long	result;

	index = 0;
	sign = 1;
	result = 0;
	while ((nptr[index] >= 9 && nptr[index] <= 13) || nptr[index] == ' ')
		index++;
	if (nptr[index] == '+')
		index++;
	else if (nptr[index] == '-')
	{
		sign = -1 * sign;
		index++;
	}
	while (nptr[index] >= 48 && nptr[index] <= 57)
	{
		result = 10 * result + (nptr[index] - '0');
		index++;
	}
	if (!(result > 0 && result <= 2147483647))
		return (-1);
	return (result * sign);
}

int	valid_just_numbers(char *argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (!(argv[i] >= 48 && argv[i] <= 57))
			return (-1);
		i++;
	}
	return (1);
}
