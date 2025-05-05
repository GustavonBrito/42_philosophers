/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustavo-linux <gustavo-linux@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 10:33:22 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/05/05 01:23:28 by gustavo-lin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

int init_validations(int argc, char **argv);
int	ft_atol(const char *nptr);
int valid_just_numbers(char **argv);

typedef struct s_rules
{
	int             philo_num;      // Número de filósofos
	long            time_to_die;    // Tempo máximo SEM comer antes de morrer (em ms)
	long            time_to_eat;    // Tempo para comer (em ms)
	long            time_to_sleep;  // Tempo para dormir (em ms)
	int             must_eat;       // (Opcional) Quantas vezes cada filósofo deve comer
	int             someone_died;   // Flag para parar tudo quando alguém morrer

	long            start_time;     // Marca o início da simulação (em ms)
	pthread_mutex_t *forks;         // Array de mutexes: cada garfo é um mutex
	pthread_mutex_t m_write;        // Mutex para garantir que prints não se misturem
}	t_rules;

typedef struct s_philo
{
	int             id;             // ID único do filósofo (de 1 a n)
	int             meals;          // Quantas vezes este filósofo já comeu
	long            last_meal;      // Timestamp da última refeição
	pthread_t       thread;         // A thread do filósofo
	pthread_mutex_t *left_fork;     // Ponteiro para o garfo da esquerda (mutex)
	pthread_mutex_t *right_fork;    // Ponteiro para o garfo da direita (mutex)
	t_rules         *rules;         // Ponteiro para t_rules
}	t_philo;

#endif