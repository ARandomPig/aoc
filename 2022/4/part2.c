/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 23:03:36 by tomoron           #+#    #+#             */
/*   Updated: 2024/10/28 23:46:30 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"

static void parse_range(int *start, int *end, char *range)
{
	*start = ft_atoi(range);
	while(*range && *range != '-')
		range++;
	if(*range)
		range++;
	*end = ft_atoi(range);
}

static int	range_contains_next(char **ranges)
{
	int r1_start;
	int r1_end;
	int r2_start;
	int r2_end;

	if(!ranges)
		return(0);
	parse_range(&r1_start, &r1_end, ranges[0]);
	parse_range(&r2_start, &r2_end, ranges[1]);
	if(r1_end < r2_start)
		return(0);
	if(r2_end < r1_start)
		return(0);
	return(1);
}

long int resolve_part2(char *input, char **split)
{
	(void)input;
	(void)split;
	int i;
	int res;

	i = 0;
	res = 0;
	while(split[i])
	{
		if(range_contains_next(ft_split(split[i], ',')))
			res++;
		i++;
	}
	return(res);
}
