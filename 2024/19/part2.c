/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 23:03:36 by tomoron           #+#    #+#             */
/*   Updated: 2024/12/19 13:06:39 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "libft/libft.h"

typedef struct s_mem
{
	char *line;
	long int value;
	struct s_mem *next;
} t_mem;

static long int mem_get(t_mem *mem, char *line)
{
	while(mem)
	{
		if(mem->line == line)
			return(mem->value);
		mem = mem->next;
	}
	return(0);
}

static void mem_add(t_mem **mem, char *line, long int val)
{
	t_mem *new;

	new = malloc(sizeof(t_mem));
	new->line = line;
	new->value = val;
	new->next = *mem;
	*mem = new;
}

static void free_mem(t_mem **mem)
{
	t_mem *tmp;

	while(*mem)
	{
		tmp = (*mem)->next;
		free(*mem);
		*mem = tmp;
	}
}

static long int check_line(char *line, char **colors, int rec)
{
	int i;
	int len;
	long int res;
	static t_mem *mem;

	i = 0;
	if(!*line)
		return(1);
	res = mem_get(mem, line);
	if(res)
		return(res);
	while(colors[i])
	{
		len = ft_strlen(colors[i]);
		if(!ft_strncmp(line, colors[i], len))
			res += check_line(line + len, colors, 1);
		i++;
	}
	(void)rec;
	(void)mem_add;
	(void)free_mem;
	if(rec)
		mem_add(&mem, line, res);
	else
		free_mem(&mem);
	return(res);
}

long int resolve_part2(char *input, char **split)
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
		res += check_line(*split, colors, 0);
		split++;
	}
	ft_free_str_arr(colors);
	return(res);
}
