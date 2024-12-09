/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 23:03:36 by tomoron           #+#    #+#             */
/*   Updated: 2024/12/09 14:23:36 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"

static void add_nbr(int **res, int nb, int index)
{
	int free_space;
	 
	free_space = index % 2;
	if(index)
		index /= 2;
	while(nb > 0)
	{
		if(free_space)
			**res = -1;
		else
			**res = index;
		(*res)++;
		nb--;
	}
}

static int *get_nbrs(char *input, size_t *len)
{
	int i;
	int *nbrs;
	int *res;

	*len = 0;
	i = 0;
	while(input[i] && ft_isdigit(input[i]))
	{
		*len += input[i] - '0';
		i++;
	}
	res = malloc(*len * sizeof(int));
	nbrs = res;
	i = 0;
	while(input[i])
	{
		add_nbr(&nbrs, input[i] - '0', i);
		i++;
	}
	return(res);
}

static void frag_disk(int *disk, int len)
{
	int *fs_ptr;
	int *end_ptr;	

	fs_ptr = disk;
	end_ptr = disk + (len - 1);
	while(end_ptr != fs_ptr)
	{
		while(*fs_ptr != -1 && fs_ptr < end_ptr)
			fs_ptr++;
		while(*end_ptr == -1 && end_ptr > fs_ptr)
			end_ptr--;
		*fs_ptr = *end_ptr;	
		*end_ptr = -1;
	}
}

long int resolve_part1(char *input, char **split)
{
	(void)split;
	int *disk;
	size_t len;
	size_t i;	
	long int res;
	disk = get_nbrs(input, &len);
	frag_disk(disk, len);
	res = 0;
	i = 0;
	while(i < len)
	{
		if(disk[i] != -1)
			res += disk[i] * i;
		i++;
	}
	free(disk);
	return(res);
}


