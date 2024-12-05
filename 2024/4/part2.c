/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 23:03:36 by tomoron           #+#    #+#             */
/*   Updated: 2024/12/04 10:48:38 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"

static int is_word(char **split, int y, int x)
{
	if(split[y][x] != 'A')
		return(0);
	if(x == 0 || y == 0 || !split[y + 1])
		return(0);
	if(((split[y - 1][x - 1] == 'M' && split[y + 1][x + 1] == 'S') || 
		(split[y - 1][x - 1] == 'S' && split[y + 1][x + 1] == 'M')) && 
		((split[y - 1][x + 1] == 'S' && split[y + 1][x - 1] == 'M') || 
		(split[y - 1][x + 1] == 'M' && split[y + 1][x - 1] == 'S')))
		return(1);
	return(0);
	
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
			if(is_word(split, i, j))
			{
				printf("%c", split[i][j]);
				res++;
			}
			else
				printf(".");
			j++;
		}
		printf("\n");
		i++;
	}
	i = 0;
	return(res);
}
