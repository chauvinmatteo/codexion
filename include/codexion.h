/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchauvin <mchauvin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 11:37:19 by mchauvin          #+#    #+#             */
/*   Updated: 2026/05/11 13:41:43 by mchauvin         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include "coders.h"
# include "dongles.h"
# include "parsing.h"
# include "typedef.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef struct s_codex
{
	t_parsing	parser;
	t_coders	*coders;
	t_dongles	*dongles;

}				t_codex;

int				ft_check_args(int ac, char **av, t_codex *values);

#endif