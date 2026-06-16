/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchauvin <mchauvin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 14:38:27 by mchauvin          #+#    #+#             */
/*   Updated: 2026/06/16 11:08:17 by mchauvin         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

int	ft_simulation_state(t_codex *data)
{
	int	status;

	pthread_mutex_lock(&data->state_lock);
	status = data->running;
	pthread_mutex_unlock(&data->state_lock);
	return (status);
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

void	*monitor_routine(void *args)
{
	t_codex	*codex;
	int		i;

	codex = (t_codex *)args;
	while (1)
	{
		i = 0;
		while (i < codex->parser.number_of_coders)
		{
			if (check_death(codex, i) == 1)
				return (NULL);
			i++;
		}
		if (check_all_compile(codex) == 1)
		{
			pthread_mutex_lock(&codex->state_lock);
			codex->running = 0;
			pthread_mutex_unlock(&codex->state_lock);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_codex	codex;

	if (ft_check_args(ac, av, &codex) == -1)
		return (1);
	if (init_codexion(&codex) == -1)
		return (1);
	start_codexion(&codex);
	free_codexion(&codex);
	return (0);
}
