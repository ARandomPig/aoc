/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 23:03:36 by tomoron           #+#    #+#             */
/*   Updated: 2024/12/08 13:38:45 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"

static int *get_numbers(char *line, int *len)
{
	int i;
	int *res;

	*len = 0;
	i = 0;
	while(line[i])
	{
		if(line[i] == ' ')
			(*len)++;
		i++;
	}
	*len += 1;
	res = malloc((*len) * sizeof(int));
	i = 0;
	while(*line)
	{
		res[i] = ft_atoi(line);
		i++;
		while(ft_isdigit(*line))
			line++;
		while(*line && !ft_isdigit(*line))
			line++;
	}
	return(res);
}

static int next_op(char *op, int i)
{
	while(i >= 0 && op[i] == '+')
	{
		op[i] = '*';
		i--;
	}
	if(i < 0)
		return(0);
	if(i >= 0)
		op[i] = '+';
	return(1);
}

static long int test_nbrs(long int test_val, int *nbrs, char *op, int len)
{
	int i;
	long int tmp;

	tmp = 0;
	while(tmp != test_val)
	{
		tmp = *nbrs;
		i = 1;
		while(i < len)
		{
			if(op[i - 1] == '+')
				tmp += nbrs[i];
			else if(op[i - 1] == '*')
				tmp *= nbrs[i];
			if(tmp > test_val)
				break;
			i++;
		}
		if(!next_op(op, i - 1) && tmp != test_val)
		{
			free(nbrs);
			free(op);
			return(0);
		}
		
	}
	free(nbrs);
	free(op);
	return(test_val);
}

static long int check_line(char *line)
{
	long int test_val;
	int		*nbrs;
	int		len;
	char	*op;

	test_val = atol(line);
	while(ft_isdigit(*line))
		line++;
	while(*line && !ft_isdigit(*line))
		line++;
	nbrs = get_numbers(line, &len);
	op = malloc(len);
	ft_memset(op, '*', len);
	return(test_nbrs(test_val, nbrs, op, len));
}

long int resolve_part1(char *input, char **split)
{
	(void)input;
	long int res;
	
	res = 0;
	while(*split)
	{
		res+= check_line(*split);
		split++;
	}
	return(res);
}
