/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niida <niida@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 15:18:56 by niida             #+#    #+#             */
/*   Updated: 2024/03/21 18:54:40 by niida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef enum s_type
{
	NONE,
	BLANK,
	IDENTIFIER,
	OP,
	RESERVED,
}			t_type;

typedef struct s_token
{
	char	*start;
	size_t	len;
	t_type	type;
	char	*next;
}			t_token;

int	is_metacharacter(int c)
{
	return (strchr("|&; 	", c));
}

int	is_blank(int c)
{
	return ( c == ' ' || c == '\t');
}

int	is_quote(int c)
{
	return (strchr("()<>", c));
}

int	is_op(char *c)
{
	static char	op[] = {"||", "&", "&&", ";", ";;", "(", ")", "|", "\n"};

	while (*op)
	{
		if (strncmp());
	}
	return ();
}

int	is_identifier(char *c)
{
	return (isalnum(*c) || *c == '_');
}

t_token *lst_new(char *s)
{
	t_token	*word;

	word = malloc(sizeof(*word));
	word->start = s;
	word->len = 0;
	word->type = BLANK;
	word->next = NULL;
}

void	lst_add(t_token *lst, t_token *new)
{
	if (!lst)
		return (NULL);
	while (lst)
		lst = lst->next;
	lst->next = new;
}

//if is_quote, wait for close quote pair
//{{'(', ')'}, {'<', '>'}, '"', '\''}
//
/*
 * 1. flag metacharacter.
 * 2. close quoting metacharacter "" '' ()
 * 3. implement tokenize error handling, such as unclosed metacharacter
 * 4. expand metacharacter, remove metacharacter and create new node
 */
char	**tokenize(char *line)
{
	char	*c;
	t_token	*word;
	bool	quote_open;

	c = line;
	quote_open = false;
	while (*c)
	{
		if (is_quote(c))
		{
			++word->len;
			if (quote_open)
				quote_open = false;
			else
			{
				quote_open = true;
				tokenize(++c);
			}
		}
		else if (is_metacharacter(*c))
		{
			word->type = BLANK;
		}
		else if (word->type == BLANK)
		{
			word = lst_new(c);
			word->type = IDENTIFIER;
			++word->len;
		}
		else
			++word->len;
		++c;
	}
	return (token);
}
