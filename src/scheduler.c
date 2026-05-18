/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchauvin <mchauvin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 11:35:03 by mchauvin          #+#    #+#             */
/*   Updated: 2026/05/13 14:11:54 by mchauvin         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

t_ticket *fifo (t_queue *queue, t_ticket **prev)
{
    t_ticket *head;
    head = queue->head;
    *prev = NULL;
    return (head);
}