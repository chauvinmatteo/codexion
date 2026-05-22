/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchauvin <mchauvin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 13:58:46 by mchauvin          #+#    #+#             */
/*   Updated: 2026/05/21 11:52:11 by mchauvin         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/coders.h"
#include "../include/codexion.h"
#include "../include/queue.h"

void	print_action(t_codex *data, int id, char *action)
{
	long	time_now;

	pthread_mutex_lock(&data->print_lock);
	if (data->running == 1)
	{
		time_now = get_time_in_ms() - data->start_time;
		printf("%ld %d %s\n", time_now, id, action);
	}
	pthread_mutex_unlock(&data->print_lock);
}

static void	assign_locks(t_coders *coder, pthread_mutex_t **first,
		pthread_mutex_t **second)
{
	if (coder->id % 2 == 0)
	{
		*first = &coder->left_dongle->lock;
		*second = &coder->right_dongle->lock;
	}
	else
	{
		*first = &coder->right_dongle->lock;
		*second = &coder->left_dongle->lock;
	}
}

void	*coders_routine(void *args)
{
	t_coders	*coder;

	coder = (t_coders *)args;
	assign_locks(coder, &coder->first_lock, &coder->second_lock);
	while (ft_simulation_state(coder->data) == 1)
	{
		waiting_turn(coder, &coder->data->wait_list);
		take_and_compile(coder);
		pass_token(&coder->data->wait_list);
		debug_and_refactor(coder);
	}
	return (NULL);
}
