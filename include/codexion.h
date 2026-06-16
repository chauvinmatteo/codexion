/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchauvin <mchauvin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 11:37:19 by mchauvin          #+#    #+#             */
/*   Updated: 2026/06/16 11:09:34 by mchauvin         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include "coders.h"
# include "dongles.h"
# include "parsing.h"
# include "queue.h"
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_dongles	t_dongles;
typedef struct s_coders		t_coders;
typedef struct s_queue		t_queue;
typedef struct s_ticket		t_ticket;
typedef struct s_parsing	t_parsing;

typedef struct s_codex
{
	t_parsing				parser;
	t_coders				*coders;
	t_dongles				*dongles;
	t_queue					wait_list;
	pthread_mutex_t			print_lock;
	pthread_mutex_t			state_lock;
	long					start_time;
	int						running;
	pthread_t				monitor_thread;

}							t_codex;

int							ft_simulation_state(t_codex *data);
int							init_global_mutexes(t_codex *data);
int							init_codexion(t_codex *data);
int							start_codexion(t_codex *data);
void						*monitor_routine(void *args);
void						free_codexion(t_codex *data);
long						get_time_in_ms(void);
#endif