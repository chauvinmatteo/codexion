/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongles.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchauvin <mchauvin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 09:54:59 by mchauvin          #+#    #+#             */
/*   Updated: 2026/05/18 11:04:49 by mchauvin         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef DONGLES_H
# define DONGLES_H

# include "codexion.h"
# include <pthread.h>

typedef struct s_dongles
{
	pthread_mutex_t	lock;
	int				in_use;
	long			cooldown_end;

}					t_dongles;

#endif