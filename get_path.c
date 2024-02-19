/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgnanaso <rgnanaso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 17:19:47 by rgnanaso          #+#    #+#             */
/*   Updated: 2024/02/19 17:21:18 by rgnanaso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	get_path(char *command, char *command_path)
{
	int		fd[2];
	char	*args[3];
	pid_t	pid;
	char	buf[256];

	args[0] = "which";
	args[1] = command;
	args[2] = NULL;

	pipe(fd);
	pid = fork();
	if (pid == -1)
	{
		printf("error");
		return (0);
	}
	else if (pid == 0)
	{
		dup2(fd[1], 1);
		execve("/bin/which", args, NULL);
	}
	else
		read(fd[0], command_path, 255);
	return (0);
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