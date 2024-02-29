/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgnanaso <rgnanaso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 17:19:47 by rgnanaso          #+#    #+#             */
/*   Updated: 2024/02/29 17:21:59 by rgnanaso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_path(char *command)
{
	int		fd[2];
	char	*args[3];
	pid_t	pid;
	char	*buf;

	args[0] = "which";
	args[1] = command;
	args[2] = NULL;
	buf = malloc(256);
	pipe(fd);
	pid = fork();
	if (pid == -1)
	{
		printf("error");
		return (0);
	}
	else if (pid == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		execve("/bin/which", args, NULL);
	}
	else
	{
		wait(NULL);
		read(fd[0], buf, 255);
	}
	return (buf);
}

void	rm_newline(char *command_path)
{
	int	i;

	i = 0;
	while (command_path[i])
	{
		if (command_path[i] == 10)
			command_path[i] = 0;
		i++;
	}
}