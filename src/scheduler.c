/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchauvin <mchauvin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 11:35:03 by mchauvin          #+#    #+#             */
/*   Updated: 2026/05/26 16:52:01 by mchauvin         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

t_ticket	*fifo(t_queue *queue, t_ticket **prev)
{
	t_ticket	*head;

	head = queue->head;
	*prev = NULL;
	return (head);
}

static int	closer_to_burnout(t_coders *current, t_coders *best)
{
	if (current->last_compile_start < best->last_compile_start)
		return (1);
	if (current->last_compile_start == best->last_compile_start
		&& current->id < best->id)
		return (1);
	return (0);
}

t_ticket	*edf(t_queue *queue, t_ticket **prev)
{
	t_ticket	*current;
	t_ticket	*current_prev;
	t_ticket	*best;
	t_ticket	*best_prev;

	best = queue->head;
	best_prev = NULL;
	current = queue->head->next;
	current_prev = queue->head;
	while (current != NULL)
	{
		if (closer_to_burnout(current->coders, best->coders) == 0)
		{
			best = current;
			best_prev = current_prev;
		}
		current_prev = current;
		current = current->next;
	}
	*prev = best_prev;
	return (best);
}
