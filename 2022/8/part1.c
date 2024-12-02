/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 23:03:36 by tomoron           #+#    #+#             */
/*   Updated: 2024/10/29 21:11:32 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"

static int check_dir(char **map, int pos[2], int dir[2])
{
	char height;
	
	height = map[pos[1]][pos[0]];
	pos[0] += dir[0];
	pos[1] += dir[1];
	while(pos[1] >= 0 && map[pos[1]] && pos[0] >= 0 && map[pos[1]][pos[0]])
	{
		if(map[pos[1]][pos[0]] >= height)
			return(0);
		pos[0] += dir[0];
		pos[1] += dir[1];
	}
	return(1);
}

long int resolve_part1(char *input, char **split)
{
	(void)input;
	int x;
	int y;
	int res;

	res = 0;
	y = 0;
	while(split[y])
	{
		x = 0;
		while(split[y][x])
		{
			if(check_dir(split, (int[2]){x, y},(int[2]){1,0}) || 
				check_dir(split, (int[2]){x, y},(int[2]){-1,0}) ||
				check_dir(split, (int[2]){x, y},(int[2]){0,1}) || 
				check_dir(split, (int[2]){x, y},(int[2]){0,-1}))
				res++;
			x++;
		}
		y++;
	}
	return(res);
}
