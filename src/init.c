/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchauvin <mchauvin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 10:23:25 by mchauvin          #+#    #+#             */
/*   Updated: 2026/06/16 11:09:57 by mchauvin         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

int	init_global_mutexes(t_codex *data)
{
	pthread_mutex_init(&data->print_lock, NULL);
	pthread_mutex_init(&data->state_lock, NULL);
	pthread_mutex_init(&data->wait_list.queue_lock, NULL);
	data->wait_list.head = NULL;
	data->wait_list.tail = NULL;
	data->wait_list.size = 0;
	if (data->parser.number_of_coders == 1)
		data->wait_list.free_tickets = 1;
	else
		data->wait_list.free_tickets = data->parser.number_of_coders / 2;
	data->running = 1;
	return (0);
}

static void	init_array(t_codex *data)
{
	int	i;

	i = 0;
	while (i < (data->parser.number_of_coders))
	{
		pthread_mutex_init(&data->dongles[i].lock, NULL);
		pthread_mutex_init(&data->coders[i].personal_lock, NULL);
		pthread_cond_init(&data->coders[i].turn_cond, NULL);
		data->dongles[i].available_at = 0;
		data->coders[i].id = i + 1;
		data->coders[i].compile_numbers = 0;
		data->coders[i].can_compile = 0;
		data->coders[i].data = data;
		data->coders[i].left_dongle = &data->dongles[i];
		data->coders[i].right_dongle = &data->dongles[(i + 1)
			% data->parser.number_of_coders];
		i++;
	}
}

int	init_codexion(t_codex *data)
{
	int	i;

	i = 0;
	init_global_mutexes(data);
	data->coders = malloc(sizeof(t_coders) * (data->parser.number_of_coders));
	data->dongles = malloc(sizeof(t_dongles) * (data->parser.number_of_coders));
	if (data->coders == NULL || data->dongles == NULL)
	{
		fprintf(stderr, "Error: malloc initialisation problems arised.\n");
		pthread_mutex_destroy(&data->print_lock);
		pthread_mutex_destroy(&data->state_lock);
		pthread_mutex_destroy(&data->wait_list.queue_lock);
		if (data->coders != NULL)
			free(data->coders);
		if (data->dongles != NULL)
			free(data->dongles);
		return (-1);
	}
	init_array(data);
	return (0);
}
