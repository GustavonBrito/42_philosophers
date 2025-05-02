/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustavo-linux <gustavo-linux@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 10:33:22 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/05/02 02:58:04 by gustavo-lin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <sys/time.h>

typedef struct s_timeval {
    time_t      tv_sec;     // Segundos desde 1º de janeiro de 1970 (Epoch)
    suseconds_t tv_usec;    // Microssegundos
} t_timeval;

typedef struct s_rules
{
	int	philo_num;
	int	times_to_die;
	int	times_to_eat;
	int	times_to_sleep;
}	t_rules;


typedef struct s_philo
{
	int 		id;
	int 		current_state;
	t_timeval	*last_meal_time;
	t_rules		*rules;
}	t_philo;

#endif