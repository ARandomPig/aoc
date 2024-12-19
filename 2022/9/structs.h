/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 12:50:02 by tomoron           #+#    #+#             */
/*   Updated: 2024/12/19 18:08:53 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

#include <stdint.h>
 
typedef struct s_instruction
{
	int dir[2];
	int rep;	
}	t_instruction;

typedef struct s_pos
{
	int pos[2];
	struct s_pos *next;
} t_pos;
#endif
