/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchauvin <mchauvin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 13:58:46 by mchauvin          #+#    #+#             */
/*   Updated: 2026/06/16 11:06:58 by mchauvin         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

static void	assign_locks(t_coders *coder)
{
	if (coder->left_dongle < coder->right_dongle)
	{
		coder->first_dongle = coder->left_dongle;
		coder->second_dongle = coder->right_dongle;
	}
	else
	{
		coder->first_dongle = coder->right_dongle;
		coder->second_dongle = coder->left_dongle;
	}
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

void	*coders_routine(void *args)
{
	t_coders	*coder;

	coder = (t_coders *)args;
	assign_locks(coder);
	if (coder->data->parser.number_of_coders == 1)
	{
		pthread_mutex_lock(&coder->first_dongle->lock);
		print_action(coder->data, coder->id, "has taken a dongle");
		while (ft_simulation_state(coder->data) == 1)
			usleep(1000);
		pthread_mutex_unlock(&coder->first_dongle->lock);
		return (NULL);
	}
	if (coder->id % 2 == 0)
		usleep(5000);
	while (ft_simulation_state(coder->data) == 1)
	{
		waiting_turn(coder, &coder->data->wait_list);
		take_and_compile(coder);
		pass_token(&coder->data->wait_list);
		debug_and_refactor(coder);
	}
	return (NULL);
}
