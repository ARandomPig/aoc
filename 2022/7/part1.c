/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 23:03:36 by tomoron           #+#    #+#             */
/*   Updated: 2024/10/29 20:32:22 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"
#include "structs.h"

static t_directory *create_directory(char *name, t_directory *parent, void *next)
{
	t_directory *res;

	res = malloc(sizeof(t_directory));
	res->is_dir = 1;
	res->name = name;
	res->next = next;
	res->elements = 0;
	res->parent = parent;
	return(res);
}

static char *get_word(char *input)
{
	int len;
	char *res;

	len = 0;
	while(input[len] != ' ' && input[len])
		len++;
	res = malloc(len + 1);
	res[len] = 0;
	ft_memcpy(res, input, len);
	return(res);
}

static void change_directory(char *arg, t_directory *root, t_directory **current)
{
	t_directory *tmp;

	if(!ft_strcmp(arg, "/"))
		*current = root;
	else if (!ft_strcmp(arg, ".."))
	{
		if((*current)->parent)
			*current = (*current)->parent;
	}
	else
	{
		tmp = (*current)->elements;
		while(tmp)
		{
			if(tmp->is_dir && !ft_strcmp(tmp->name, arg))
			{
				*current = tmp;
				break;
			}
			tmp = tmp->next;
		}
	}
}

static t_file *create_file(char *name, int size, t_file *next)
{
	t_file *res;

	res = malloc(sizeof(t_file));
	res->is_dir = 0;
	res->name = name;
	res->size = size;
	res->next = next;
	return(res);
}

static char **list(char **input, t_directory *dir)
{
	char *first_arg;
	char *second_arg;

	(void)dir;
	while(*input && **input != '$')
	{
		first_arg = get_word(*input);
		second_arg = *input + ft_strlen(first_arg) + 1;
		if(!ft_strcmp(first_arg, "dir"))
			dir->elements = create_directory(second_arg, dir, dir->elements);
		else
			dir->elements = create_file(second_arg, ft_atoi(first_arg), dir->elements);
		free(first_arg);
		input++;
	}
	return(input);
}

static char **exec_command(char **input, t_directory *root, t_directory **current)
{
	char *cmd;

	if(**input != '$')
		return(input + 1);
	cmd = get_word(*input + 2);
	if(!ft_strcmp(cmd, "cd"))
	{
		change_directory(*input + 5 , root, current);
		free(cmd);
		return(input + 1);
	}
	else if (!ft_strcmp(cmd, "ls"))
	{
		free(cmd);
		return(list(input + 1, *current));
	}
	free(cmd);
	return(input + 1);
}

static t_directory *parse_input(char **input)
{
	t_directory *root;
	t_directory *current;

	root = create_directory("/", 0, 0);
	current = root;
	while(*input)
	{
		input = exec_command(input, root, &current);
	}
	return(root);
}

static long int dir_size(t_directory *dir,int depth, long int *res)
{
	long int tmp_dir_size;
	long int size;
	t_file *tmp;
	
	tmp = dir->elements;
	size = 0;
	while(tmp)
	{
		if(tmp->is_dir)
		{
			tmp_dir_size = dir_size((t_directory *)tmp, depth + 1, res);
			if(tmp_dir_size <= 100000)
			{
				*res += tmp_dir_size;
			}
			size += tmp_dir_size;
		}
		else
			size += tmp->size;
		tmp = tmp->next;
	}
	return(size);
}

static void free_dir(t_directory *dir)
{
	void *tmp;
	
	while(dir->elements)
	{
		if(((t_directory *)dir->elements)->is_dir)
		{
			tmp = ((t_directory*)dir->elements)->next;
			free_dir(dir->elements);
			dir->elements = tmp;
		}
		else
		{
			tmp = ((t_directory*)dir->elements)->next;
			free(dir->elements);
			dir->elements = tmp;
		}
	}
	free(dir);
}

long int resolve_part1(char *input, char **split)
{
	(void)input;
	t_directory *dir;
	long int res;

	res = 0;
	dir = parse_input(split);
	dir_size(dir, 0, &res);
	free_dir(dir);
	return(res);
}
