/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchauvin <mchauvin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 11:37:19 by mchauvin          #+#    #+#             */
/*   Updated: 2026/05/21 11:52:04 by mchauvin         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include "coders.h"
# include "dongles.h"
# include "parsing.h"
# include "queue.h"
# include "typedef.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef struct s_codex
{
	t_parsing		parser;
	t_coders		*coders;
	t_dongles		*dongles;
	t_queue			wait_list;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	state_lock;
	long			start_time;
	int				running;
	pthread_t		monitor_thread;

}					t_codex;

int					ft_check_args(int ac, char **av, t_codex *values);
long				get_time_in_ms(void);
int					ft_simulation_state(t_codex *data);
void				print_action(t_codex *data, int id, char *action);
void				free_codexion(t_codex *data);
int					start_codexion(t_codex *data);
int					init_codexion(t_codex *data);

int					ft_enqueue(t_queue *queue, t_coders *coder);
t_coders			*ft_dequeue(t_queue *queue, char *scheduler);
void				waiting_turn(t_coders *coders, t_queue *queue);
void				take_and_compile(t_coders *coder);
void				pass_token(t_queue *queue);
void				debug_and_refactor(t_coders *coder);

#endif