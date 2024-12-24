/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 23:03:36 by tomoron           #+#    #+#             */
/*   Updated: 2024/12/24 16:05:51 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "libft/libft.h"

typedef struct s_op
{
	char name1[4];
	char name2[4];
	char op;
} t_op;

typedef struct s_vars
{
	char name[4];
	t_op *op;
	unsigned nb:1;
	struct s_vars *next;
} t_vars;


static void add_var(t_vars **vars, char *line, t_op *op)
{
	t_vars *new;

	new = malloc(sizeof(t_vars));
	memcpy(new->name, line, 3);
	new->name[3] = 0;
	new->nb = 0;
	if(!op)
	{
		while(*line != ':' && *line)
			line++;
		while(!ft_isdigit(*line) && *line)
			line++;
		new->nb = ft_atoi(line);
	}
	new->op = op;
	new->next = *vars;
	*vars = new;
}

static void get_res(char *res, char *line)
{
	while(*line != '>' && *line)
		line++;	
	line += 2;
	memcpy(res, line, 3);
	res[3] = 0;
}

static void handle_line(t_vars **vars, char *line)
{
	t_op *new_op;
	char val[4];

	new_op = malloc(sizeof(t_op));
	new_op->op = 0;
	memcpy(new_op->name1, line, 3);
	new_op->name1[3] = 0;
	while(*line != ' ' && *line)
		line++;
	while(*line == ' ')
		line++;
	if(*line == 'O')
		new_op->op = 1;
	if(*line == 'A')
		new_op->op = 2;
	if(*line == 'X')
		new_op->op = 3;
	while(*line != ' ' && *line)
		line++;
	while(*line == ' ')
		line++;
	memcpy(new_op->name2, line, 3);
	new_op->name2[3] = 0;
	get_res(val, line);
	add_var(vars, val, new_op);
}

static t_vars *get_var(t_vars *vars, char *name)
{
	while(vars)
	{
		if(!ft_strcmp(vars->name, name))
			return(vars);
		vars = vars->next;
	}
	return(0);
}

static int get_value(t_vars *all, t_vars *var)
{
	if(!var->op)
		return(var->nb);
	if(var->op->op == 1)
		return(get_value(all, get_var(all, var->op->name1)) | get_value(all, get_var(all, var->op->name2)));
	if(var->op->op == 2)
		return(get_value(all, get_var(all, var->op->name1)) & get_value(all, get_var(all, var->op->name2)));
	if(var->op->op == 3)
		return(get_value(all, get_var(all, var->op->name1)) ^ get_value(all, get_var(all, var->op->name2)));
	return(0);
}

long int resolve_part1(char *input, char **split)
{
	(void)input;
	t_vars *vars;
	t_vars *tmp;
	uint64_t res;
	
	vars = 0;
	res = 0;
	while((*split)[3] == ':')
	{
		add_var(&vars, *split, 0);
		split++;
	}
	while(*split)
	{
		handle_line(&vars, *split);
		split++;
	}
	tmp = vars;
	while(tmp)
	{
		if(tmp->name[0] == 'z' && ft_isdigit(tmp->name[1]) && ft_isdigit(tmp->name[2]))
		{
			if(get_value(vars, tmp))
				res += (uint64_t)1 << ft_atoi(tmp->name + 1);
		}
		tmp = tmp->next;
	}
	return(res);
}
