/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchauvin <mchauvin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 10:23:25 by mchauvin          #+#    #+#             */
/*   Updated: 2026/05/21 10:32:14 by mchauvin         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/coders.h"
#include "../include/codexion.h"

int	init_global_mutexes(t_codex *data)
{
	pthread_mutex_init(&data->print_lock, NULL);
	pthread_mutex_init(&data->state_lock, NULL);
	pthread_mutex_init(&data->wait_list.queue_lock, NULL);
	data->wait_list.head = NULL;
	data->wait_list.tail = NULL;
	data->wait_list.size = 0;
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
		data->dongles[i].in_use = 0;
		data->dongles[i].cooldown_end = 0;
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
		fprintf(stderr, "Error: malloc initialisation problems arised.");
		pthread_mutex_destroy(&data->print_lock);
		return (-1);
	}
	init_array(data);
	return (0);
}

void	*monitor_routine(void *args)
{
	t_codex		*codex;
	int			i;
	int			finished_coders;
	long long	current_time;

	codex = (t_codex *)args;
	while (1)
	{
		finished_coders = 0;
		i = 0;
		while (i < codex->parser.number_of_coders)
		{
			pthread_mutex_lock(&codex->coders[i].personal_lock);
			current_time = codex->coders[i].last_compile_start;
			if (codex->coders[i].compile_numbers >= codex->parser.number_of_compiles_required)
				finished_coders += 1;
			pthread_mutex_unlock(&codex->coders[i].personal_lock);
			if (get_time_in_ms()
				- current_time >= codex->parser.time_to_burnout)
			{
				pthread_mutex_lock(&codex->print_lock);
				pthread_mutex_lock(&codex->state_lock);
				codex->running = 0;
				printf("%ld %d has burned out\n", get_time_in_ms()
					- codex->start_time, codex->coders[i].id);
				;
				pthread_mutex_unlock(&codex->state_lock);
				pthread_mutex_unlock(&codex->print_lock);
				return (NULL);
			}
			i++;
		}
		if (finished_coders == codex->parser.number_of_coders)
		{
			pthread_mutex_lock(&codex->state_lock);
			codex->running = 0;
			pthread_mutex_unlock(&codex->state_lock);
			return (NULL);
		}
	}
}

int	start_codexion(t_codex *data)
{
	int	i;

	i = 0;
	data->start_time = get_time_in_ms();
	while (i < data->parser.number_of_coders)
	{
		data->coders[i].last_compile_start = data->start_time;
		pthread_create(&data->coders[i].thread, NULL, coders_routine,
			&data->coders[i]);
		i++;
	}
	pthread_create(&data->monitor_thread, NULL, monitor_routine, data);
	pthread_join(data->monitor_thread, NULL);
	i = 0;
	while (i < data->parser.number_of_coders)
	{
		pthread_join(data->coders[i].thread, NULL);
		i++;
	}
	return (0);
}
