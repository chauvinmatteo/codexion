/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchauvin <mchauvin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 14:38:27 by mchauvin          #+#    #+#             */
/*   Updated: 2026/05/21 13:30:26 by mchauvin         ###   ########lyon.fr   */
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
