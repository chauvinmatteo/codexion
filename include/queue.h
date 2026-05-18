/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchauvin <mchauvin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 10:33:04 by mchauvin          #+#    #+#             */
/*   Updated: 2026/05/18 11:08:25 by mchauvin         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUEUE_H
# define QUEUE_H

# include "codexion.h"
# include "typedef.h"
# include <pthread.h>

typedef struct s_ticket
{
	t_coders		*coders;
	struct s_ticket	*next;
	struct s_ticket	*prev;
}					t_ticket;

typedef struct s_queue
{
	t_ticket		*head;
	t_ticket		*tail;
	int				size;
	pthread_mutex_t	queue_lock;
}					t_queue;

t_ticket			*fifo(t_queue *queue, t_ticket **prev);
#endif