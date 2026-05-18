/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchauvin <mchauvin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 13:58:46 by mchauvin          #+#    #+#             */
/*   Updated: 2026/05/12 17:09:22 by mchauvin         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/coders.h"
#include "../include/codexion.h"
#include <unistd.h>

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
	t_coders		*coders;
	pthread_mutex_t	*first_lock;
	pthread_mutex_t	*second_lock;

	coders = (t_coders *)args;
	assign_locks(coders, &first_lock, &second_lock);
	while ((ft_simulation_state(coders->data) == 1))
	{
		pthread_mutex_lock(first_lock);
		print_action(coders->data, coders->id, "has taken a dongle");
		pthread_mutex_lock(second_lock);
		print_action(coders->data, coders->id, "has taken a dongle");
		print_action(coders->data, coders->id, "is compiling");
		pthread_mutex_lock(&coders->personal_lock);
		coders->last_compile_start = get_time_in_ms();
		coders->compile_numbers++;
		pthread_mutex_unlock(&coders->personal_lock);
		usleep(coders->data->parser.time_to_compile * 1000);
		pthread_mutex_unlock(first_lock);
		pthread_mutex_unlock(second_lock);
		print_action(coders->data, coders->id, "is debugging");
		usleep(coders->data->parser.time_to_debug * 1000);
		print_action(coders->data, coders->id, "is refactoring");
		usleep(coders->data->parser.time_to_refactor * 1000);
	}
	return (NULL);
}
