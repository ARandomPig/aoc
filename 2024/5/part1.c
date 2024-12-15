/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 23:03:36 by tomoron           #+#    #+#             */
/*   Updated: 2024/12/15 19:20:04 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"

typedef struct s_orders
{
	int left;
	int right;
	struct s_orders *next;
}	t_orders;

static void add_order(char *line, t_orders **orders)
{
	t_orders *new;

	new = malloc(sizeof(t_orders));
	new->left = ft_atoi(line);
	while(ft_isdigit(*line))
		line++;
	line++;
	new->right = ft_atoi(line);
	new->next = *orders;
	*orders = new;
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

static int *get_numbers(char *line, int *len)
{
	int *res;
	int i;

	*len = count_char(line, ',') + 1;
	res = malloc(*len * sizeof(int));	
	i = 0;
	while(*line)
	{
		res[i] = ft_atoi(line);
		while(ft_isdigit(*line))
			line++;
		if(*line == ',')
			line++;
		i++;	
	}
	return(res);

}

static int respect_order(int *nbrs, t_orders *orders, int len)
{
	int i;
	int j;

	i = 0;
	while(i < len)
	{
		j = 0;
		while(j < len)
		{
			if(i != j)	
			{
				if(nbrs[i] == orders->left && nbrs[j] == orders->right && i > j)	
					return(0);
			}
			j++;
		}
		i++;
	}
	return(1);
}

static int is_ordered(int *nbrs, t_orders *orders, int len)
{

	while(orders)
	{
		if(!respect_order(nbrs, orders, len))
			return(0);
		orders = orders->next;	
	}
	return(1);
}

static long int check_line(char *line, t_orders *orders)
{
	int *nbrs;	
	int len;
	int res;

	nbrs = get_numbers(line, &len);
	if(!is_ordered(nbrs, orders, len))
	{
		free(nbrs);
		return(0);
	}
	
	res = nbrs[(len / 2)];
	free(nbrs);
	return(res);
}

long int resolve_part1(char *input, char **split)
{
	(void)input;
	t_orders *orders;
	t_orders *tmp;
	long int res;

	orders = 0;
	while((*split)[2] == '|')
	{
		add_order(*split, &orders);
		split++;
	}
	res = 0;
	while(*split)
	{
		res += check_line(*split, orders);
		split++;
	}
	while(orders)
	{
		tmp = orders->next;
		free(orders);
		orders = tmp;
	}
	return(res);
}
