/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 23:03:36 by tomoron           #+#    #+#             */
/*   Updated: 2024/10/29 21:21:44 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"

static int check_dir(char **map, int pos[2], int dir[2])
{
	char height;
	int dist;
	
	height = map[pos[1]][pos[0]];
	pos[0] += dir[0];
	pos[1] += dir[1];
	dist = 1;
	while(pos[1] >= 0 && map[pos[1]] && pos[0] >= 0 && map[pos[1]][pos[0]])
	{
		if(map[pos[1]][pos[0]] >= height)
			return(dist);
		pos[0] += dir[0];
		pos[1] += dir[1];
		dist++;
	}
	return(dist - 1);
}

static int get_score(char **map,int x, int y)
{
	return(check_dir(map, (int[2]){x, y},(int[2]){1,0}) *
		check_dir(map, (int[2]){x, y},(int[2]){-1,0}) *
		check_dir(map, (int[2]){x, y},(int[2]){0,1}) *
		check_dir(map, (int[2]){x, y},(int[2]){0,-1}));
}

long int resolve_part2(char *input, char **split)
{
	(void)input;
	int x;
	int y;
	int res;
	int score;

	res = 0;
	y = 0;
	while(split[y])
	{
		x = 0;
		while(split[y][x])
		{
			score = get_score(split, x, y);
			if(score > res)
				res = score;
			x++;
		}
		y++;
	}
	return(res);
}
