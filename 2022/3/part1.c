/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 23:03:36 by tomoron           #+#    #+#             */
/*   Updated: 2024/07/18 00:06:18 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"

static long int char_value(char c)
{
	if(c >= 'A' && c <= 'Z')
		return((c - 'A') + 27);
	return((c - 'a') + 1);
}

static long int resline(char *line)
{
	char	*ptr;
	char	*found;
	int		len;
	int		i;
	
	len = ft_strlen(line);
	ptr = line + (len / 2);
	i = 0;
	while(i < len /2)
	{
		found = ft_strchr(ptr, line[i]);
		if(found)
			return(char_value(*found));	
		i++;
	}
	return(0);
}

long int resolve_part1(char *input, char **split)
{
	(void)input;
	long int	res;
	int			i;

	res = 0;
	i = 0;
	while(split[i])
	{
		res += resline(split[i]);
		i++;
	}
	return(res);
}
