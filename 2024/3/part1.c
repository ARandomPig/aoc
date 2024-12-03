/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 23:03:36 by tomoron           #+#    #+#             */
/*   Updated: 2024/12/03 10:22:09 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"

static int get_instruction(char **line, int *n1, int *n2)
{
	int i;

	if(ft_strncmp(*line, "mul(", 4))
		return(0);
	*line += 4;
	i = 0;
	*n1 = ft_atoi(*line);
	while(ft_isdigit((*line)[i]))
		i++;
	if(!i)
		return(0);
	*line += i;
	if(**line != ',')
		return(0);
	(*line)++;
	i = 0;
	*n2 = ft_atoi(*line);
	while(ft_isdigit((*line)[i]))
		i++;
	if(!i)
		return(0);
	*line += i;
	return(**line == ')');
}

static long int res_line(char *line)
{
	int res;
	int n1;
	int n2;
	
	res = 0;
	while(*line)
	{
		if(get_instruction(&line, &n1, &n2))	
			res += n1 * n2;
		line++;
	}
	return(res);
}

long int resolve_part1(char *input, char **split)
{
	(void)input;
	long int res;

	res = 0;
	while(*split)
	{
		res += res_line(*split);	
		split++;
	}
	return(res);
}
