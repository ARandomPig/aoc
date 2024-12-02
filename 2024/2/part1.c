/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 23:03:36 by tomoron           #+#    #+#             */
/*   Updated: 2024/12/02 11:22:15 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"

static void skip_nbr(char **line)
{
	while(ft_isdigit(**line))
		(*line)++;
	while(**line == ' ')
		(*line)++;
}

static long int check_line(char *line)
{
	int left;
	int right;
	int asc;

	left = ft_atoi(line);
	skip_nbr(&line);
	asc = -1;
	while(*line)
	{
		right = ft_atoi(line);
		skip_nbr(&line);
		if(right == left || (left > right && asc == 1) || (left < right && asc == 0))
			return(0);
		if(left > right)
			asc = 0;
		if(left < right)
			asc = 1;
		if(left - right > 3 || left - right < -3)
			return(0);
		left = right;
	}
	return(1);
}

long int resolve_part1(char *input, char **split)
{
	(void)input;
	long int res;
	int i;

	i = 0;
	res = 0;
	while(split[i])
	{
		res += check_line(split[i]);
		i++;
	}
	return(res);
}
