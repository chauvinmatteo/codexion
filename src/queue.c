/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchauvin <mchauvin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 10:46:21 by mchauvin          #+#    #+#             */
/*   Updated: 2026/06/16 10:18:40 by mchauvin         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

int	ft_enqueue(t_queue *queue, t_coders *coder)
{
	t_ticket	*new_coder;

	new_coder = malloc(sizeof(t_ticket));
	if (!new_coder)
		return (-1);
	new_coder->coders = coder;
	new_coder->next = NULL;
	if (queue->head == NULL)
	{
		queue->head = new_coder;
		queue->tail = new_coder;
	}
	else
	{
		queue->tail->next = new_coder;
		queue->tail = new_coder;
	}
	queue->size++;
	return (0);
}

t_coders	*ft_dequeue(t_queue *queue, char *scheduler)
{
	t_ticket	*prev;
	t_ticket	*target;
	t_coders	*coder;

	target = NULL;
	prev = NULL;
	if (queue->size == 0)
		return (NULL);
	if (strcmp(scheduler, "fifo") == 0)
		target = fifo(queue, &prev);
	else if (strcmp(scheduler, "edf") == 0)
		target = edf(queue, &prev);
	if (prev == NULL)
		queue->head = target->next;
	else
		prev->next = target->next;
	if (target == queue->tail)
		queue->tail = prev;
	coder = target->coders;
	free(target);
	queue->size--;
	return (coder);
}
