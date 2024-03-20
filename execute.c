/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgnanaso <rgnanaso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:16:44 by rgnanaso          #+#    #+#             */
/*   Updated: 2024/03/20 16:09:42 by rgnanaso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	exec_first(t_pipex *pipex)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (0);
	else if (pid == 0)
	{
		dup2(pipex->file[0], STDIN_FILENO);
		dup2(pipex->pip[1], STDOUT_FILENO);
		close(pipex->pip[0]);
		if (execve(pipex->command_path[0], pipex->command[0], NULL) == -1)
			printf("failed 1");
	}
	return (1);
}

//Inverser stdin et stdout

int	execute(t_pipex *pipex, char *argv[], int argc)
{
	int		i;
	int		fd[2];
	pid_t	pid;

	i = -1;
	//exec_first(pipex);
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
			if (execve(pipex->command_path[i], pipex->command[i], NULL) == -1)
				printf("failed 3");
		}
		else
		{
			close(fd[1]);
			dup2(fd[0], STDIN_FILENO);
		}
	}
	dup2(pipex->file[1], STDOUT_FILENO);
	execve(pipex->command_path[argc - 2], pipex->command[argc - 2], NULL);
	//exec_last(pipex, argv, argc);
	return (0);
}

int	exec_last(t_pipex *pipex, char *argv[], int argc)
{
	pid_t	pid;

	if (pid < 0)
		return (0);
	else if (pid == 0)
	{
		dup2(pipex->file[1], STDOUT_FILENO);
		if (execve(pipex->command_path[argc - 4], pipex->command[argc - 4], NULL) == -1)
			printf("failed2");
	}
	return (1);
}
