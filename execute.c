/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgnanaso <rgnanaso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:16:44 by rgnanaso          #+#    #+#             */
/*   Updated: 2024/04/23 15:38:36 by rgnanaso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	execute(t_pipex *pipex, char *argv[], char *envp[], int argc)
{
	int		i;
	int		fd[2];
	int		fd_here_doc;
	pid_t	pid;

	i = -1;
	if (pipex->here_doc == 1)
	{
		here_doc(argv);
		fd_here_doc = open("here_docu", O_RDONLY);
		dup2(fd_here_doc, STDIN_FILENO);
	}
	else
		dup2(pipex->file[0], STDIN_FILENO);
	while (++i < argc - 4 - pipex->here_doc)
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
			{
				free_pipex(pipex);
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			close(fd[1]);
			dup2(fd[0], STDIN_FILENO);
		}
	}
	close(pipex->file[0]);
	dup2(pipex->file[1], STDOUT_FILENO);
	if (execve(pipex->command_path[argc - 4 - pipex->here_doc], pipex->command[argc - 4 - pipex->here_doc], envp) == -1)
	{
			free_pipex(pipex);
			exit(EXIT_FAILURE);
	}
	free_pipex(pipex);
	exit(0);
}
