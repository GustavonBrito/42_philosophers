/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_validations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustavo-linux <gustavo-linux@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 22:40:40 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/05/07 00:02:25 by gustavo-lin      ###   ########.fr       */
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
