/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchauvin <mchauvin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 09:53:59 by mchauvin          #+#    #+#             */
/*   Updated: 2026/05/12 11:17:06 by mchauvin         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODERS_H
# define CODERS_H

# include "dongles.h"
# include "parsing.h"
# include "typedef.h"
typedef struct s_coders
{
	int				id;
	int				compile_numbers;
	long long		last_compile_start;
	t_dongles		*left_dongle;
	t_dongles		*right_dongle;
	pthread_t		thread;
	pthread_mutex_t	personal_lock;
	t_codex			*data;

}					t_coders;

void				*coders_routine(void *args);
#endif