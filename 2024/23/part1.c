/* ************************************************ ************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 23:03:36 by tomoron           #+#    #+#             */
/*   Updated: 2024/12/23 22:26:48 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libft/libft.h"

typedef struct s_connected t_connected;

typedef struct s_computer 
{
	t_connected *connected;
	char name[3];
	struct s_computer *next;	
}	t_computer;

typedef struct s_done
{
	t_computer *lst[3];
	struct s_done *next;
} t_done;

typedef struct s_connected 
{
	t_computer *comp;
	struct s_connected *next;

} t_connected;

static t_computer *get_computer(t_computer *list, char *name)
{
	while(list)
	{
		if(!ft_strcmp(list->name, name))
			return(list);
		list = list->next;
	}
	return(0);
}

static void add_to_computer(t_computer **computers, char *computer, char *other)
{
	t_computer *tmp;
	t_connected *new;

	tmp = *computers;
	while(tmp)
	{
		if(!ft_strcmp(tmp->name, computer))
			break;
		tmp = tmp->next;
	}
	if(!tmp)
	{
		tmp = malloc(sizeof(t_computer));
		memcpy(tmp->name, computer, 3);
		tmp->next = *computers;
		tmp->connected = 0;
		*computers = tmp;
	}
	new = malloc(sizeof(t_connected));
	new->comp = get_computer(*computers, other);
	new->next = tmp->connected;
	tmp->connected = new;
}

static void parse_line(t_computer **list, char *line)
{
	char c1[3];
	char c2[3];
	c1[0] = line[0];
	c1[1] = line[1];
	c1[2] = 0;
	c2[0] = line[3];
	c2[1] = line[4];
	c2[2] = 0;
	add_to_computer(list, c1, c2);
	add_to_computer(list, c2, c1);
}

static int is_connected(t_computer *c1, t_computer *c2)
{
	t_connected *tmp;

	if(!c1 || !c2)
		return(0);
	tmp = c1->connected;
	while(tmp)
	{
		if(tmp->comp == c2)
			return(1);
		tmp = tmp->next;
	}
	tmp = c2->connected;
	while(tmp)
	{
		if(tmp->comp == c1)
			return(1);
		tmp = tmp->next;
	}
	return(0);
}

int is_done(t_done *done, t_computer *c1, t_computer *c2, t_computer *c3)
{
	while(done)
	{
		if((done->lst[0] == c1 || done->lst[0] == c2 || done->lst[0] == c3) && (done->lst[1] == c1 || done->lst[1] == c2 || done->lst[1] == c3) && (done->lst[2] == c1 || done->lst[2] == c2 || done->lst[2] == c3))
			return(1);
		done = done->next;
	}
	return(0);
}

void add_done(t_done **done, t_computer *c1, t_computer *c2, t_computer *c3)
{
	t_done *new;

	new = malloc(sizeof(t_done));
	new->lst[0] = c1;
	new->lst[1] = c2;
	new->lst[2] = c3;
	new->next = *done;
	*done = new;
}

int get_res(t_computer *input)
{
	t_connected *tmp1;
	t_connected *tmp2;
	t_done *done;
	int res;

	res = 0;
	done = 0;
	while(input)
	{
		tmp1 = input->connected;
		while(tmp1)
		{
			tmp2 = input->connected;
			while(tmp2)
			{
				if(tmp1 != tmp2)
				{
					if(is_connected(tmp1->comp, tmp2->comp) && !is_done(done, input, tmp1->comp, tmp2->comp))
					{
						res += (*input->name == 't' || *tmp1->comp->name == 't' || *tmp2->comp->name == 't');
						add_done(&done, input, tmp1->comp, tmp2->comp);
					}
				}
				tmp2 = tmp2->next;
			}
			tmp1 = tmp1->next;
		}
		input = input->next;
	}
	return(res);
}

long int resolve_part1(char *line, char **split)
{
	(void)line;
	t_computer *input;
	int res;

	res = 0;
	input = 0;
	while(*split)
	{
		parse_line(&input, *split);
		split++;
	}
	res = get_res(input);
	return(res);
}
