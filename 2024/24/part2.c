/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 23:03:36 by tomoron           #+#    #+#             */
/*   Updated: 2024/12/24 18:44:00 by tomoron          ###   ########.fr       */
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
	if(!var)
		return(0);
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

int is_input(char *name)
{
	return((*name == 'x' || *name == 'y') && ft_isdigit(name[1]) && ft_isdigit(name[2]));
}

int is_output(char *name)
{
	return(*name == 'z' && ft_isdigit(name[1]) && ft_isdigit(name[2]));
}

int is_first(t_vars *var)
{
	int nb;

	if(is_input(var->op->name1) && is_input(var->op->name2))
	{
		nb = ft_atoi(var->op->name1 + 1);
		if(nb == 0)
			return(1);
	}
	return(0);
}

int is_valid_carry(t_vars *all, t_vars *cur)
{
	while(all)
	{
		if(all->op && (!ft_strcmp(cur->op->name1, all->name) || !ft_strcmp(cur->op->name2, all->name)))
			if(all->op->op == 2 && is_input(all->op->name1) && ft_atoi(all->op->name1 + 1) != 0)
			{
				printf("%s\n", all->name);
				return(0);
			}
		all = all->next;
	}
	return(1);
}

int check_before_xor(t_vars *all, t_vars *cur)
{
	while(all)
	{
		if(all->op && (!ft_strcmp(cur->name, all->op->name1) || !ft_strcmp(cur->name, all->op->name2)))
			if(all->op->op == 1)
			{
				printf("%s\n", cur->name);
				return(0);
			}
		all = all->next;
	}
	return(1);
}

void get_wrong(t_vars *vars)
{
	t_vars *tmp;
	t_vars *start;
	int max_out;

	tmp = vars;
	start = vars;
	max_out = 0;
	while(tmp)
	{
		if(is_output(tmp->name) && ft_atoi(tmp->name + 1) > max_out)
			max_out = ft_atoi(tmp->name + 1);
		tmp = tmp->next;
	}
	while(vars)
	{
		if(vars->op && !is_first(vars))
		{
			if(vars->op->op == 3 && is_input(vars->op->name1) && is_input(vars->op->name2) && is_output(vars->name))
				printf("%s\n", vars->name);
			if(vars->op->op == 3 && !is_input(vars->op->name1) && !is_input(vars->op->name2) && !is_output(vars->name))
				printf("%s\n", vars->name);
			if(vars->op->op == 2 && is_output(vars->name))
				printf("%s\n", vars->name);
			if(vars->op->op == 1 && is_output(vars->name) && ft_atoi(vars->name + 1) != max_out)
				printf("%s\n", vars->name);
			if(vars->op->op == 3 && !is_input(vars->op->name1) && !is_input(vars->op->name2) && is_output(vars->name))
				is_valid_carry(start, vars);
			if(vars->op->op == 3 && is_input(vars->op->name1) && is_input(vars->op->name2) && !is_output(vars->name))
				check_before_xor(start, vars);

		}
		vars = vars->next;
	}
}

void show_wrong(t_vars *vars)
{
	uint64_t vals[2];
	uint64_t expected;
	uint64_t value;
	int max_bit;
	int i;

	value = 0;
	vals[0] = 0;
	vals[1] = 0;
	max_bit = 0;	
	i = 0;
	while(vars)
	{
		if(vars->name[0] == 'z' && ft_isdigit(vars->name[1]) && ft_isdigit(vars->name[2]))
		{
			if(ft_atoi(vars->name + 1) > max_bit)
				max_bit = ft_atoi(vars->name + 1);
			if(get_value(vars, vars))
				value += (uint64_t)1 << ft_atoi(vars->name + 1);
		}
		if(vars->name[0] == 'x' && ft_isdigit(vars->name[1]) && ft_isdigit(vars->name[2]))
		{
			if(get_value(vars, vars))
				vals[0] += (uint64_t)1 << ft_atoi(vars->name + 1);
		}
		if(vars->name[0] == 'y' && ft_isdigit(vars->name[1]) && ft_isdigit(vars->name[2]))
		{
			if(get_value(vars, vars))
				vals[1] += (uint64_t)1 << ft_atoi(vars->name + 1);
		}
		vars = vars->next;
	}
	expected = vals[0] + vals[1];
	while(i <= max_bit)
	{
		if((expected & (1 << max_bit)) != (value & (1 << i)))
			printf("error on %d\n", i);
		i++;
	}
}

long int resolve_part2(char *input, char **split)
{
	(void)input;
	t_vars *vars;
	
	vars = 0;
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
//	show_wrong(vars);
	get_wrong(vars);
	printf("order it yourself idgaf\n");
	return(0);
}
