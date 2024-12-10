/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 23:03:36 by tomoron           #+#    #+#             */
/*   Updated: 2024/12/10 12:32:48 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"

static long int find_trails(char **map, int pos[2])
{
	char c;
	long int res;

	c = map[pos[0]][pos[1]];
	res = 0;
	if(c == '9')
		return(1);
	if(map[pos[0] + 1] && map[pos[0] + 1][pos[1]] == c + 1)
		res += find_trails(map, (int [2]){pos[0] + 1, pos[1]});
	if(pos[0] - 1 >= 0 && map[pos[0] - 1][pos[1]] == c + 1)
		res += find_trails(map, (int [2]){pos[0] - 1, pos[1]});
	if(map[pos[0]][pos[1] + 1] && map[pos[0]][pos[1] + 1] == c + 1)
		res += find_trails(map, (int [2]){pos[0], pos[1] + 1});
	if(pos[1] - 1 >= 0 && map[pos[0]][pos[1] - 1] == c + 1)
		res += find_trails(map, (int [2]){pos[0], pos[1] - 1});
	return(res);	
}

long int resolve_part2(char *input, char **split)
{
	(void)input;
	int i;
	int j;
	long int res;

	i = 0;
	res = 0;
	while(split[i])
	{
		j = 0;
		while(split[i][j])
		{
			if(split[i][j] == '0')
				res += find_trails(split, (int [2]){i, j});
			j++;
		}
		i++;
	}
	return(res);
}
