/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niida <niida@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:05:31 by niida             #+#    #+#             */
/*   Updated: 2024/03/16 16:47:51 by niida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>
#define _CHILD 0

void	fatal_error(const char *msg) __attribute__((noreturn));
void	fatal_error(const char *msg)
{
	dprintf(STDERR_FILENO, "Fatal Error: %s\n", msg);
	exit(1);
}

char	*path_join(char *dir, char *exe)
{
	size_t	exe_len;
	size_t	dir_len;
	char	*full;
	char	*full_path;

	dir_len = ft_strlen(dir);
	exe_len = ft_strlen(exe);
	full = malloc(dir_len + exe_len + 2);
	if (!full)
		return (NULL);
	full_path = full;
	while (*dir)
		*full++ = *dir++;
	*full++ = '/';
	while (*exe)
		*full++ = *exe++;
	*full = '\0';
	return (full_path);
}

char	*get_path(char *exe)
{
	char	**dir;
	char	**directories;
	char	*path;
	char	**cmd;

	dir = ft_split(getenv("PATH"), ':');
	directories = dir;
	cmd = ft_split(exe, ' ');
	while (*dir)
	{
		path = path_join(*dir++, cmd[0]);
		if (access(path, X_OK) == 0)
			break ;
		free(path);
		path = NULL;
	}
	free(directories);
	return (path);
}

int	interpret(char *line)
{
	extern char	**environ;
	char		*argv[] = {line, NULL};
	pid_t		pid;
	int			wstatus;

	pid = fork();
	if (pid < 0)
		fatal_error("fork");
	else if (pid == _CHILD)
	{
		execve(line, argv, environ);
		execve(get_path(line), argv, environ);
		fatal_error("command not found");
	}
	else
	{
		wait(&wstatus);
		return (WEXITSTATUS(wstatus));
	}
}

int	main(void)
{
	char	*line;

	rl_outstream = stderr;
	while (1)
	{
		line = readline("minishell$ ");
		if (line == NULL)
			break ;
		if (*line)
			add_history(line);
		interpret(line);
		free(line);
	}
	exit(0);
}
