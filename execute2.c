/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgnanaso <rgnanaso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:16:44 by rgnanaso          #+#    #+#             */
/*   Updated: 2024/03/20 15:32:30 by rgnanaso         ###   ########.fr       */
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
	int		fd;
	pid_t	pid;

	i = 0;
	exec_first(pipex);
	while (++i < argc - 4)
	{
		pid = fork();
		if (pid < 0)
			return (0);
		else if (pid == 0)
		{
			dup2(pipex->pip[0], STDIN_FILENO);
			dup2(pipex->file[1], STDOUT_FILENO);
			close(pipex->pip[1]);
			execve(pipex->command_path[i], pipex->command[i], NULL);
		}
		else
		{
			fd = dup(pipex->file[1]);
			dup2(fd, pipex->pip[1]);
		}
	}
	exec_last(pipex, argv, argc);
	return (0);
}

int	exec_last(t_pipex *pipex, char *argv[], int argc)
{
	pid_t	pid;

	if (pid < 0)
		return (0);
	else if (pid == 0)
	{
		close(pipex->pip[1]);
		dup2(pipex->pip[0], STDIN_FILENO);
		dup2(pipex->file[1], STDOUT_FILENO);
		if (execve(pipex->command_path[argc - 4], pipex->command[argc - 4], NULL) == -1)
			printf("failed2");
	}
	return (1);
}
