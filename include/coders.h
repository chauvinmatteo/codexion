/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchauvin <mchauvin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 09:53:59 by mchauvin          #+#    #+#             */
/*   Updated: 2026/05/21 13:29:50 by mchauvin         ###   ########lyon.fr   */
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
	int				can_compile;
	long long		last_compile_start;
	t_dongles		*left_dongle;
	t_dongles		*right_dongle;
	pthread_mutex_t	*first_lock;
	pthread_mutex_t	*second_lock;
	pthread_t		thread;
	pthread_mutex_t	personal_lock;
	pthread_cond_t	turn_cond;
	t_codex			*data;

}					t_coders;

void				*coders_routine(void *args);
#endif