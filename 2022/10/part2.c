/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 23:03:36 by tomoron           #+#    #+#             */
/*   Updated: 2024/12/19 21:40:11 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"

static long int get_nbr(char *line)
{
	while(*line && !ft_isdigit(*line) && *line != '-')
		line++;
	return(atol(line));
}

static char **create_map(void)
{
	char **res;
	int i;

	res = malloc(7 * sizeof(char *));
	res[6] = 0;
	i = 0;
	while(i < 6)
	{
		res[i] = malloc(41);
		res[i][40] = 0;
		ft_memset(res[i], '.', 40);
		i++;
	}
	return(res);
}

long int resolve_part2(char *input, char **split)
{
	(void)input;
	long int reg;
	int cycle;
	char **map;
	int flag;

	map = create_map();
	cycle = 0;
	reg = 1;
	flag = 0;
	if(reg - (cycle % 40) >= -1 && reg - (cycle % 40) <= 1)
		map[cycle / 40][cycle % 40] = '#';
	while(*split)
	{
		if(**split == 'a')
		{
			if(!flag)
				flag = 1;
			else
			{
				flag = 0;
				reg += get_nbr(*split);
				split++;
			}
		}
		else
			split++;
		cycle++;
		if(reg - (cycle % 40) >= -1 && reg - (cycle % 40) <= 1)
			map[cycle / 40][cycle % 40] = '#';
	}
	cycle = 0;
	while(map[cycle])
	{
		printf("%s\n", map[cycle]);
		cycle ++;
	}
	ft_free_str_arr(map);
	return(-1);
}
