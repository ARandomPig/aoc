/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 23:03:36 by tomoron           #+#    #+#             */
/*   Updated: 2024/12/19 11:46:36 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"

static int check_line(char *line, char **colors)
{
	int i;
	int len;

	i = 0;
	if(!*line)
		return(1);
	while(colors[i])
	{
		len = ft_strlen(colors[i]);
		if(!ft_strncmp(line, colors[i], len))
			if(check_line(line + len, colors))
				return(1);
		i++;
	}
	return(0);
}

long int resolve_part1(char *input, char **split)
{
	(void)input;
	char **colors;
	long int res;

	res = 0;
	if(!*split)
		return(-1);
	colors = ft_split_set(*split, ", ");
	split++;
	while(*split)
	{
		res += check_line(*split, colors);
		split++;
	}
	ft_free_str_arr(colors);
	return(res);
}
