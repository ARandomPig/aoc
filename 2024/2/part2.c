/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 23:03:36 by tomoron           #+#    #+#             */
/*   Updated: 2024/12/02 12:20:40 by tomoron          ###   ########.fr       */
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

static long int check_line(char *line, int ignore)
{
	int left;
	int right;
	int asc;
	int i;

	if(ignore == 0)
		skip_nbr(&line);
	left = ft_atoi(line);
	skip_nbr(&line);
	asc = -1;
	i = 1;
	while(*line)
	{
		if(i == ignore)
			skip_nbr(&line);
		if(!*line)
			break;
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
		i++;
	}
	return(1);
}

static int count_char(char *str, char c)
{
	int res;
	
	res = 0;
	while(*str)
	{
		if(*str == c)
			res++;
		str++;
	}
	return(res);
}

long int resolve_part2(char *input, char **split)
{
	(void)input;
	long int res;
	int i;
	int j;
	int len;

	i = 0;
	res = 0;
	while(split[i])
	{
		if(check_line(split[i], -1))
			res++;
		else
		{
			len = count_char(split[i], ' ') + 1;
			j = 0;
			while(j < len)
			{
				if(check_line(split[i], j))
				{
					res++;
					break;
				}
				j++;
			}
		}
		i++;
	}
	return(res);
}
