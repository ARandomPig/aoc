/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   res.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 16:02:52 by tomoron           #+#    #+#             */
/*   Updated: 2024/07/17 22:58:17 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft/libft.h"

int get_score(int a, int b)
{
	if(b == 1)
	{
		if(a == 1)
			return(3);
		if(a == 2)
			return(1);
		if(a == 3)
			return(2);
	}

	if(b == 2)
		return(a + 3);

	if(a == 1)
		return(2 + 6);
	if(a == 2)
		return(3 + 6);
	return(1 + 6);
		
}

long int resolve(char *input)
{
	char	**split;
	int		i;
	long int	res;

	split = ft_split(input, '\n');
	i = 0;
	res = 0;
	while(split[i])
	{
		printf("round : %s\n", split[i]);
		switch(split[i][0])
		{
			case 'A':
				split[i][0] = 1;
				break;
			case 'B':
				split[i][0] = 2;
				break;
			case 'C':
				split[i][0] = 3;
				break;
		}
		switch(split[i][2])
		{
			case 'X':
				split[i][2] = 1;
				break;
			case 'Y':
				split[i][2] = 2;
				break;
			case 'Z':
				split[i][2] = 3;
				break;
		}
		res += get_score(split[i][0], split[i][2]);
		printf("%d vs %d\n", split[i][0], split[i][2]);
		printf("round : %d, score : %d\n", i + 1, get_score(split[i][0], split[i][2]));
		i++;
	}
	return(res);
}
