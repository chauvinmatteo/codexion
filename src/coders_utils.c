/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchauvin <mchauvin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 11:17:15 by mchauvin          #+#    #+#             */
/*   Updated: 2026/05/21 14:11:28 by mchauvin         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"
#include <unistd.h>

void	waiting_turn(t_coders *coders, t_queue *queue)
{
	pthread_mutex_lock(&queue->queue_lock);
	if (queue->free_tickets > 0 && queue->size == 0)
		queue->free_tickets--;
	else
	{
		ft_enqueue(queue, coders);
		while (coders->can_compile == 0)
			pthread_cond_wait(&coders->turn_cond, &queue->queue_lock);
		coders->can_compile = 0;
	}
	pthread_mutex_unlock(&queue->queue_lock);
}

void	take_and_compile(t_coders *coder)
{
	pthread_mutex_lock(coder->first_lock);
	print_action(coder->data, coder->id, "has taken a dongle");
	pthread_mutex_lock(coder->second_lock);
	print_action(coder->data, coder->id, "has taken a dongle");
	print_action(coder->data, coder->id, "is compiling");
	pthread_mutex_lock(&coder->personal_lock);
	coder->last_compile_start = get_time_in_ms();
	coder->compile_numbers++;
	pthread_mutex_unlock(&coder->personal_lock);
	usleep(coder->data->parser.time_to_compile * 1000);
	pthread_mutex_unlock(coder->first_lock);
	pthread_mutex_unlock(coder->second_lock);
}

void	pass_token(t_queue *queue)
{
	t_coders	*next_coder;

	pthread_mutex_lock(&queue->queue_lock);
	next_coder = ft_dequeue(queue, "fifo");
	if (next_coder != NULL)
	{
		next_coder->can_compile = 1;
		pthread_cond_broadcast(&next_coder->turn_cond);
	}
	else
		queue->free_tickets++;
	pthread_mutex_unlock(&queue->queue_lock);
}

void	debug_and_refactor(t_coders *coder)
{
	print_action(coder->data, coder->id, "is debugging");
	usleep(coder->data->parser.time_to_debug * 1000);

	print_action(coder->data, coder->id, "is refactoring");
	usleep(coder->data->parser.time_to_refactor * 1000);
}