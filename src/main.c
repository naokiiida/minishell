/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niida <niida@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:05:31 by niida             #+#    #+#             */
/*   Updated: 2024/02/21 20:58:05 by niida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	main(void)
//{
//	char	*rl;
//
//	rl = readline("mini > ");
//	printf("%s\n", rl);
//	return (0);
//}

// Define the invert_case_line function here
int	invert_case_line(count, key) int count, key;
{
	register int start, end;
	int direction;

	(void)key;
	start = rl_point;

	if (count < 0)
	{
		direction = -1;
		count = -count;
	}
	else
		direction = 1;

	/* Find the end of the range to modify. */
	end = start + (count * direction);

	/* Force it to be within range. */
	if (end > rl_end)
		end = rl_end;
	else if (end < 0)
		end = -1;

	if (start > end)
	{
		int temp = start;
		start = end;
		end = temp;
	}

	if (start == end)
		return (0);

	/* Tell readline that we are modifying the line, so save the undo
		information. */
	rl_modifying(start, end);

	for (; start != end; start += direction)
	{
		if (_rl_uppercase_p(rl_line_buffer[start]))
			rl_line_buffer[start] = _rl_to_lower(rl_line_buffer[start]);
		else if (_rl_lowercase_p(rl_line_buffer[start]))
			rl_line_buffer[start] = _rl_to_upper(rl_line_buffer[start]);
	}

	/* Move point to on top of the last character changed. */
	rl_point = end - direction;
	return (0);
}

int	main(void)
{
	char	*line;

	rl_initialize();
	rl_bind_key(CTRL('c'), invert_case_line); // Bind to 'M-c'
	line = readline("Enter a line: ");
	if (line)
	{
		if (*line)
		{
			add_history(line);
		}
		free(line);
	}
	return (0);
}
