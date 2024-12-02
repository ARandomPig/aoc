/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 23:03:36 by tomoron           #+#    #+#             */
/*   Updated: 2024/10/28 23:10:24 by tomoron          ###   ########.fr       */
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

static long int reslines(char *e1, char *e2, char *e3)
{
	int i;

	i = 0;
	while(e1[i])
	{
		if(ft_strchr(e2, e1[i]) && ft_strchr(e3, e1[i]))
			return(char_value(e1[i]));
		i++;
	}
	return(0);
}

long int resolve_part2(char *input, char **split)
{
	(void)input;
	long int	res;
	int			i;

	res = 0;
	i = 0;
	while(split[i])
	{
		int tmp;
		tmp = reslines(split[i], split[i + 1], split[i + 2]);
		res += tmp;
		i += 3;
	}
	return(res);
}
