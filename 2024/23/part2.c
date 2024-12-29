/* ************************************************ ************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 23:03:36 by tomoron           #+#    #+#             */
/*   Updated: 2024/12/29 23:49:22 by tomoron          ###   ########.fr       */
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

typedef struct s_found
{
	t_computer *comp;
	struct s_found *next;
}	t_found;

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

static int is_in_found(t_found *found, t_computer *c)
{
	while(found)
	{
		if(found->comp == c)
			return(1);
		found = found->next;
	}
	return(0);
}

static void add_found(t_found **found, t_computer *c)
{
	t_found *new;

	new = malloc(sizeof(t_found));
	new->comp = c;
	new->next = *found;
	*found = new;
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

static void find_connected(t_found **found,t_found **res, t_computer *comp)
{
	t_connected *lst;
	t_found *tmp;

	if(!comp || is_in_found(*found, comp))
		return;
	add_found(found, comp);
	if(!*res)
		add_found(res, comp);
	tmp = *res;
	while(tmp)
	{
		if(!is_connected(tmp->comp, comp))
			break;
		tmp = tmp->next;
	}
	if(!tmp)
		add_found(res, comp);
	lst = comp->connected;
	while(lst)
	{
		find_connected(found,res, lst->comp);	
		lst = lst->next;
	}
}

static void sort_list(t_found *found)
{
	t_found *cur;
	t_found *start;
	char tmp;

	start = found;
	cur = found;
	while(cur)
	{
		found = start;
		while(found->next)
		{
			if(ft_strcmp(found->comp->name, found->next->comp->name) > 0)
			{
				tmp = found->comp->name[0];
				found->comp->name[0] = found->next->comp->name[0];
				found->next->comp->name[0] = tmp;
				tmp = found->comp->name[1];
				found->comp->name[1] = found->next->comp->name[1];
				found->next->comp->name[1] = tmp;
				tmp = found->comp->name[2];
				found->comp->name[2] = found->next->comp->name[2];
				found->next->comp->name[2] = tmp;
			}
			found = found->next;
		}
		cur = cur->next;	
	}
}

static void free_found(t_found *f)
{
	t_found *tmp;

	while(f)
	{
		tmp = f->next;
		free(f);
		f = tmp;
	}
}

static int get_res(t_computer *input)
{
	t_found *found;
	t_found *res;
	t_found *tmp;
	int i;
	int max_len;
	
	res = 0;
	max_len = 0;
	while(input)
	{
		found = 0;
		tmp = 0;
		find_connected(&tmp,&found, input);
		free_found(tmp);
		i = 0;
		tmp = found;
		while(tmp)
		{
			tmp = tmp->next;
			i++;
		}
		if(i > max_len)
		{
			max_len = i;
			if(res)
				free_found(res);
			res = found;
		}
		else
			free_found(found);
		input = input->next;
	}
	tmp = res;
	i = 0;
	while(res)
	{
		sort_list(res);
		printf("%s", res->comp->name);
		if(res->next)
			printf(",");
		res = res->next;
		i++;
	}
	printf("\n");
	free_found(tmp);
	return(0);
}

static void free_connected(t_connected *co)
{
	t_connected *tmp;

	while(co)
	{
		tmp = co->next;
		free(co);
		co = tmp;
	}
}

static void free_computer(t_computer *in)
{
	t_computer *tmp;

	while(in)
	{
		tmp = in->next;
		free_connected(in->connected);
		free(in);
		in = tmp;
	}
}

long int resolve_part2(char *line, char **split)
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
	free_computer(input);
	return(res);
}
