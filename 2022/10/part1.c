/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 23:03:36 by tomoron           #+#    #+#             */
/*   Updated: 2024/12/19 21:17:39 by tomoron          ###   ########.fr       */
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

static long int nb_at_cycle(char **split, int cycle)
{
	long int reg;

	reg = 1;
	cycle--;
	while(*split && cycle >= 2)
	{
		if(**split == 'a')
		{
			if(cycle <= 1)
				break;
			reg += get_nbr(*split);
			cycle -= 2;
		}
		else
			cycle--;
		split++;
	}
	return(reg);
}

long int resolve_part1(char *input, char **split)
{
	(void)input;
	long int res;
	int cycle;
	res = 0;
	cycle = 20;
	while(cycle <= 220)
	{
		res += nb_at_cycle(split, cycle) * cycle;
		cycle += 40;
	}
	return(res);
}
