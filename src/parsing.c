/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchauvin <mchauvin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 10:00:39 by mchauvin          #+#    #+#             */
/*   Updated: 2026/05/12 16:05:43 by mchauvin         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"
#include "../include/parsing.h"

int	ft_parsed_value(t_parsing *parser)
{
	if (parser->number_of_coders <= 0 || parser->time_to_burnout <= 0
		|| parser->time_to_compile < 0 || parser->time_to_debug < 0
		|| parser->time_to_refactor < 0 || parser->dongle_cooldown < 0
		|| parser->number_of_compiles_required < 0)
	{
		fprintf(stderr, "Error: values has to be integers from 0 to int max");
		return (-1);
	}
	if (strcmp(parser->scheduler, "fifo") != 0 && strcmp(parser->scheduler,
			"edf") != 0)
	{
		fprintf(stderr, "Error: scheduler needs to be 'fifo' or 'edf'");
		return (-1);
	}
	return (0);
}

int	ft_check_int(char *av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		if (av[i] >= '0' && av[i] <= '9')
			i++;
		else
			return (-1);
	}
	return (atoi(av));
}

int	ft_check_args(int ac, char **av, t_codex *values)
{
	if (ac != 9)
	{
		fprintf(stderr,
				"Invalid format, expected:\n%s number_of_coders "
				"time_to_burnout time_to_compile time_to_debug "
				"time_to_refactor number_of_compiles_required "
				"dongle_cooldown scheduler\n",
				av[0]);
		return (-1);
	}
	values->parser.number_of_coders = ft_check_int(av[1]);
	values->parser.time_to_burnout = ft_check_int(av[2]);
	values->parser.time_to_compile = ft_check_int(av[3]);
	values->parser.time_to_debug = ft_check_int(av[4]);
	values->parser.time_to_refactor = ft_check_int(av[5]);
	values->parser.number_of_compiles_required = ft_check_int(av[6]);
	values->parser.dongle_cooldown = ft_check_int(av[7]);
	values->parser.scheduler = av[8];
	return (ft_parsed_value(&values->parser));
}
