/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchauvin <mchauvin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 10:33:04 by mchauvin          #+#    #+#             */
/*   Updated: 2026/06/16 10:30:46 by mchauvin         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUEUE_H
# define QUEUE_H

# include <pthread.h>

typedef struct s_ticket
{
	t_coders		*coders;
	struct s_ticket	*next;
}					t_ticket;

typedef struct s_queue
{
	t_ticket		*head;
	t_ticket		*tail;
	int				size;
	pthread_mutex_t	queue_lock;
	int				free_tickets;
}					t_queue;

t_ticket			*fifo(t_queue *queue, t_ticket **prev);
t_ticket			*edf(t_queue *queue, t_ticket **prev);
int					ft_enqueue(t_queue *queue, t_coders *coder);
t_coders			*ft_dequeue(t_queue *queue, char *scheduler);
#endif