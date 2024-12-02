/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:20:26 by tomoron           #+#    #+#             */
/*   Updated: 2024/10/29 18:10:36 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_file
{
	int is_dir;
	void *next;
	char *name;
	int size;
}	t_file;

typedef struct s_directory
{
	int is_dir;
	void *next;
	char *name;
	void *elements;
	struct s_directory *parent;
}	t_directory;

#endif
