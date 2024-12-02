#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_crate
{
	char letter;
	struct s_crate *prev;
}	t_crate;

typedef struct s_stack_list
{
	t_crate *crate;
	struct s_stack_list *next;
}	t_stack_list;

typedef struct s_instruction
{
	int nb;
	int from;
	int to;
}	t_instruction;

#endif
