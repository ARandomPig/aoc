/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 23:03:36 by tomoron           #+#    #+#             */
/*   Updated: 2024/12/04 10:41:12 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"

static int is_word(char **split, int y, int x, int depth, int dir)
{
	char *word = "XMAS";
	int nb;

	if(depth == 4)
		return(1);
	if( y < 0 || x < 0 || !split[y] || !split[y][x])
		return(0);
	if(split[y][x] != word[depth])
		return(0);
	nb = 0;
	if((dir == 0 || dir == 1) &&
			is_word(split, y - 1, x - 1, depth + 1, 1))
		nb++;
	if((dir == 0 || dir == 2) &&
			is_word(split, y - 1, x, depth + 1, 2))
		nb++;
	if((dir == 0 || dir == 3) &&
			is_word(split, y - 1, x + 1, depth + 1, 3))
		nb++;
	if((dir == 0 || dir == 4) &&
			is_word(split, y, x + 1, depth + 1, 4))
		nb++;
	if((dir == 0 || dir == 5) &&
			is_word(split, y + 1, x + 1, depth + 1, 5))
		nb++;
	if((dir == 0 || dir == 6) &&
			is_word(split, y + 1, x, depth + 1, 6))
		nb++;
	if((dir == 0 || dir == 7) &&
			is_word(split, y + 1, x - 1, depth + 1, 7))
		nb++;
	if((dir == 0 || dir == 8) &&
			is_word(split, y, x - 1, depth + 1, 8))
		nb++;
	return(nb);

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
			res += is_word(split, i, j, 0, 0);
			j++;
		}
		i++;
	}
	i = 0;
	return(res);
}
