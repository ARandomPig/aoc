/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 23:03:36 by tomoron           #+#    #+#             */
/*   Updated: 2024/12/01 12:36:05 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"

static void get_numbers(int *left, int *right, char **split)
{
	int i;
	int j;

	i = 0;
	while(*split)
	{
		j = 0;
		*(left + i) = ft_atoi(*split);
		while((*split)[j] >= '0' && (*split)[j] <= '9')
			j++;
		while((*split)[j] == ' ')
			j++;
		*(right + i) = ft_atoi(*split + j);
		i++;
		split++;
	}
}

int count_nb(int nb, int *list, int len)
{
	int i;
	int res;

	i = 0;
	res = 0;
	while(i < len)
	{
		if(list[i] == nb)	
			res++;
		i++;
	}
	return(res);
}

long int resolve_part2(char *input, char **split)
{
	int len;
	int *left;
	int *right;
	long int res;
	int i;
	int tmp;

	len = 0;
	i = 0;
	while(split[len])
		len++;
	left = malloc(sizeof(int) * len);	
	right = malloc(sizeof(int) * len);	
	if(!left || !right)
	{
		free(left);
		free(right);
		return(-1);
	}
	get_numbers(left, right, split);
	res = 0;
	while(i < len)
	{
		tmp = count_nb(left[i], right, len);
		res += left[i] * tmp;
		i++;
	}
	free(left);
	free(right);
	(void)input;
	return(res);
}
