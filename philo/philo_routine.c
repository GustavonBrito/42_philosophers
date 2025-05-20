/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustavo-linux <gustavo-linux@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 00:08:24 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/05/19 23:12:07 by gustavo-lin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// arquivo para criar uma funcao *void que faz toda a rotina de um filosofo, pensa, come, dorme e talvez morre.s

#include "philo.h"

void *philo_routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	pthread_t thread_dead_scan;
	void *thread_return;

	thread_return = NULL;
	think(philo);
	eat(philo);
	sleep_philo(philo);
	pthread_create(&thread_dead_scan, NULL, dead_scan, NULL);
	pthread_join(thread_dead_scan, &thread_return);
	if((long)thread_return == -1)
		return (&philo->rules->someone_died);
	return (NULL);
}
//Parei aqui verificando sobre seg fault