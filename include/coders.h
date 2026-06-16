/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchauvin <mchauvin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 09:53:59 by mchauvin          #+#    #+#             */
/*   Updated: 2026/06/16 11:07:12 by mchauvin         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODERS_H
# define CODERS_H

# include <pthread.h>

typedef struct s_codex		t_codex;
typedef struct s_dongles	t_dongles;
typedef struct s_queue		t_queue;

typedef struct s_coders
{
	int						id;
	int						compile_numbers;
	int						can_compile;
	long long				last_compile_start;
	t_dongles				*left_dongle;
	t_dongles				*right_dongle;
	t_dongles				*first_dongle;
	t_dongles				*second_dongle;
	pthread_t				thread;
	pthread_mutex_t			personal_lock;
	pthread_cond_t			turn_cond;
	t_codex					*data;

}							t_coders;

void						*coders_routine(void *args);
void						waiting_turn(t_coders *coders, t_queue *queue);
void						take_and_compile(t_coders *coder);
void						pass_token(t_queue *queue);
void						debug_and_refactor(t_coders *coder);
void						print_action(t_codex *data, int id, char *action);
int							check_death(t_codex *codex, int i);
int							check_all_compile(t_codex *codex);
#endif