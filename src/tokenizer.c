//#include "token.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>

typedef struct s_token {
	char *name;
	int value;
	struct s_token *next;
}	t_token;

typedef enum {
	NONE,
	BLANK,
	IDENTIFIER,
	OP,
	RESERVED,
}	t_type;

void lst_add(t_token *node, t_token *new)
{
	while (node)
		node = node->next;
	node->next = new;
}

t_token	*lst_new(char *name)
{
	t_token	*node;

	node = malloc(sizeof(t_token));
	if (!node)
		return (NULL);
	node->name = name;
	node->value = 0;
	node->next = NULL;
	return (node);
}

//split word and blank from a string into tokens
t_token *tokenize(char *s)
{
	t_type	type;
	t_token	*token;
	t_token	*head;

	type = NONE;
	token = lst_new(s);
	head = token;
	while (*s)
	{
		if (isspace(*s))
		{
			type = BLANK;
		}
		else if (type == BLANK)
		{
			assert(token->value == 6);
			token->next = lst_new(s);
			token = token->next;
			++token->value;
			type = IDENTIFIER;
		}
		else
		{
			++token->value;
			type = IDENTIFIER;
		}
		//printf("[%d]%c\ttype:%d\n", token->value, *s, type);
		++s;
	}
	assert(token->value == 5);
	return (head);
}

int	main(void)
{
	char *str = "hello, 	world";
	t_token	*lst_tok;

	printf("strlen:%zu\n", strlen(str));
	lst_tok = tokenize(str);
	write(1, "\n", 1);
	while (lst_tok != NULL)
	{
		write(1, "print:", 6);
		write(1, lst_tok->name, lst_tok->value);
		write(1, "\n", 1);
		lst_tok = lst_tok->next;
	};
	return (0);
}
