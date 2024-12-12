/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 23:03:36 by tomoron           #+#    #+#             */
/*   Updated: 2024/12/12 13:32:35 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "libft/libft.h"



char **create_locations(char **map)
{
	int width;
	int height;
	char **res;
	int i;

	height = 0;
	while(map[height])
		height++;
	width = 0;
	while(map[0][width])
		width++;
	res = malloc((height + 1) * sizeof(char *));	
	res[height] = 0;
	i = 0;
	while(i < height)
	{
		res[i] = malloc(width + 1);
		bzero(res[i], width + 1);
		i++;
	}
	return(res);
}

int get_area_perimetter(char **map, int pos[2], int perimetter, char **locations, char c)
{
	int res;

	if(perimetter && pos[0] >= 0 && pos[1] >= 0 && map[pos[0]] && map[pos[0]][pos[1]] && locations[pos[0]][pos[1]])
		return(0);
	if(pos[0] < 0 || pos[1] < 0 || !map[pos[0]] || map[pos[0]][pos[1]] != c)
		return(perimetter != 0);
	res = 0;
	res += !perimetter && c == map[pos[0]][pos[1]];
	if(perimetter)
		locations[pos[0]][pos[1]] = 1;
	else
		map[pos[0]][pos[1]] = '.';
	res += get_area_perimetter(map, (int [2]){pos[0] - 1, pos[1]}, perimetter, locations, c);
	res += get_area_perimetter(map, (int [2]){pos[0] + 1, pos[1]}, perimetter, locations, c);
	res += get_area_perimetter(map, (int [2]){pos[0], pos[1] - 1}, perimetter, locations, c);
	res += get_area_perimetter(map, (int [2]){pos[0], pos[1] + 1}, perimetter, locations, c);
	return(res);
}

long int calc_price(char **map, int x, int y)
{
	int area;
	int perimetter;
	char **locations;
	
	locations = create_locations(map);
	perimetter = get_area_perimetter(map, (int [2]){y, x}, 1, locations, map[y][x]);
	area = get_area_perimetter(map,(int [2]){y, x}, 0, locations, map[y][x]);
	ft_free_str_arr(locations);
	return(area * perimetter);
}

long int resolve_part1(char *input, char **split)
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
			if(split[i][j] != '.')
				res += calc_price(split, j, i);
			j++;
		}
		i++;
	}
	return(res);
}
