/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgnanaso <rgnanaso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:16:44 by rgnanaso          #+#    #+#             */
/*   Updated: 2024/03/20 17:36:17 by rgnanaso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


int	execute(t_pipex *pipex, char *argv[], char *envp[], int argc)
{
	int		i;
	int		fd[2];
	pid_t	pid;

	i = -1;
	dup2(pipex->file[0], STDIN_FILENO);
	while (++i < argc - 4)
	{
		pipe(fd);
		pid = fork();
		if (pid < 0)
			return (0);
		else if (pid == 0)
		{
			close(fd[0]);
			dup2(fd[1], STDOUT_FILENO);
			if (execve(pipex->command_path[i], pipex->command[i], envp) == -1)
				printf("failed 3");
		}
		else
		{
			close(fd[1]);
			dup2(fd[0], STDIN_FILENO);
		}
	}
	close(pipex->file[0]);
	dup2(pipex->file[1], STDOUT_FILENO);
	if (execve(pipex->command_path[argc - 4], pipex->command[argc - 4], envp) == -1)
		printf("failed 2");
	return (0);
}
