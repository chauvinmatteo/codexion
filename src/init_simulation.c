/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_simulation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchauvin <mchauvin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 10:23:25 by mchauvin          #+#    #+#             */
/*   Updated: 2026/05/11 13:38:41 by mchauvin         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/coders.h"
#include "../include/codexion.h"

int	init_codexion(t_codex *data)
{
	int	i;

	i = 0;
	data->coders = malloc(sizeof(t_coders) * (data->parser.number_of_coders));
	data->dongles = malloc(sizeof(t_dongles) * (data->parser.number_of_coders));
	if (data->coders == NULL || data->dongles == NULL)
	{
		fprintf(stderr, "Error: malloc initialisation problems arised.");
		return (-1);
	}
	while (i < (data->parser.number_of_coders))
	{
		pthread_mutex_init(&data->dongles[i].lock, NULL);
		pthread_cond_init(&data->dongles[i].cd, NULL);
		data->dongles[i].in_use = 0;
		data->dongles[i].cooldown_end = 0;
		data->coders[i].id = i + 1;
		data->coders[i].compile_numbers = 0;
		data->coders[i].data = data;
		data->coders[i].left_dongle = &data->dongles[i];
		data->coders[i].right_dongle = &data->dongles[(i + 1)
			% data->parser.number_of_coders];
		i++;
	}
	return (0);
}
void	*coder_routine(void *arg)
{
	(void)arg;
	printf("test\n");
	return (NULL);
}

int	start_codexion(t_codex *data)
{
	int	i;

	i = 0;
	while (i++ < data->parser.number_of_coders)
	{
		pthread_create(&data->coders[i].thread, NULL, coder_routine,
			&data->coders[i]);
	}
	return (0);
}

// int	main(int ac, char **av)
// {
// 	t_codex codex;
// 	int i;

// 	if (ft_check_args(ac, av, &codex) == -1)
// 		return (1);
// 	if (init_codexion(&codex) == -1)
// 		return (1);
// 	start_codexion(&codex);
// 	i = 0;
// 	while (i < codex.parser.number_of_coders)
// 	{
// 		pthread_join(codex.coders[i].thread, NULL);
// 		i++;
// 	}
// 	free(codex.coders);
// 	free(codex.dongles);
// 	return (0);
// }
