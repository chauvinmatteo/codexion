/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchauvin <mchauvin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 09:20:49 by mchauvin          #+#    #+#             */
/*   Updated: 2026/05/26 13:10:53 by mchauvin         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"
#include <sys/time.h>

long	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	free_codexion(t_codex *data)
{
	int	i;

	i = 0;
	while (i < data->parser.number_of_coders)
	{
		pthread_mutex_destroy(&data->dongles[i].lock);
		pthread_cond_destroy(&data->coders[i].turn_cond);
		pthread_mutex_destroy(&data->coders[i].personal_lock);
		i++;
	}
	pthread_mutex_destroy(&data->print_lock);
	pthread_mutex_destroy(&data->state_lock);
	if (data->coders)
		free(data->coders);
	if (data->dongles)
		free(data->dongles);
}

int	check_death(t_codex *codex, int i)
{
	long long	last_start;

	pthread_mutex_lock(&codex->coders[i].personal_lock);
	last_start = codex->coders[i].last_compile_start;
	pthread_mutex_unlock(&codex->coders[i].personal_lock);
	if (get_time_in_ms() - last_start >= codex->parser.time_to_burnout)
	{
		pthread_mutex_lock(&codex->state_lock);
		if (codex->running == 1)
		{
			codex->running = 0;
			pthread_mutex_lock(&codex->print_lock);
			printf("%ld %d has burned out\n", get_time_in_ms()
				- codex->start_time, codex->coders[i].id);
			pthread_mutex_unlock(&codex->print_lock);
		}
		pthread_mutex_unlock(&codex->state_lock);
		return (1);
	}
	return (0);
}

int	check_all_compile(t_codex *codex)
{
	int	i;
	int	finish_coders;
	int	compile_goal;

	i = 0;
	finish_coders = 0;
	compile_goal = codex->parser.number_of_compiles_required;
	if (compile_goal == -1)
		return (-1);
	while (i < codex->parser.number_of_coders)
	{
		pthread_mutex_lock(&codex->coders[i].personal_lock);
		if (codex->coders[i].compile_numbers >= compile_goal)
			finish_coders += 1;
		pthread_mutex_unlock(&codex->coders[i].personal_lock);
		i++;
	}
	if (finish_coders == codex->parser.number_of_coders)
		return (1);
	return (0);
}
