/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgnanaso <rgnanaso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:16:44 by rgnanaso          #+#    #+#             */
/*   Updated: 2024/04/30 16:43:46 by rgnanaso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute_first(t_pipex *pipex, char *envp[], char *argv[])
{
	int		i;
	char	*command_path;
	char	**command_tab;
	int		fd[2];

	i = -1;
	command_tab = ft_split(argv[i + 2 + pipex->here_doc], ' ');
	command_path = get_path(envp, command_tab[0]);
	pipe(fd);
	pipex->pid = fork();
	if (pipex->pid < 0)
		exit(0);
	else if (pipex->pid == 0)
	{
		close(fd[0]);
		if (access(argv[1], R_OK))
		{
			perror(NULL);
			exit(0);
		}
		dup2(pipex->file[0], STDOUT_FILENO);
		if (command_path == NULL)
		{
			if (argv[i + 2 + pipex->here_doc][0] == '/')
				perror(NULL);
			else
				write(STDERR_FILENO, "Command not found", 18);
			exit(127);
		}
		if (execve(command_path, command_tab, envp) == -1) //here
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

void	execute2(t_pipex *pipex, char *envp[], int argc, char *argv[])
{
	int		i;
	char	*command_path;
	char	**command_tab;
	int		fd[2];

	i = -1;
	while (++i < argc - 4 - pipex->here_doc)
	{
		command_tab = ft_split(argv[i + 2 + pipex->here_doc], ' ');
		command_path = get_path(envp, command_tab[0]);
		pipe(fd);
		pipex->pid = fork();
		if (pipex->pid < 0)
			exit(0);
		else if (pipex->pid == 0)
		{
			close(fd[0]);
			dup2(fd[1], STDOUT_FILENO);
			if (command_path == NULL)
			{
				if (argv[i + 2 + pipex->here_doc][0] == '/')
					perror(NULL);
				else
					write(STDERR_FILENO, "Command not found", 18);
				exit(127);
			}
			if (execve(command_path, command_tab, envp) == -1) //here
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
}

int	execute(t_pipex *pipex, char *argv[], char *envp[], int argc)
{
	int		i;
	char	**command_tab;
	char	*command_path;

	i = -1;
	/* if (pipex->here_doc == 1)
	{
		here_doc(argv);
		fd_here_doc = open("here_docu", O_RDONLY);
		dup2(fd_here_doc, STDIN_FILENO);
	} */
	pipex->file[0] = open(argv[1], O_RDONLY);
	dup2(pipex->file[0], STDIN_FILENO);
	//execute_first(pipex, envp, envp);
	execute2(pipex, envp, argc, argv);
	close(pipex->file[0]);

	if (access(argv[argc - 1], W_OK))
	{
		perror(NULL);
		exit(0);
	}
	pipex->file[1] =  open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	dup2(pipex->file[1], STDOUT_FILENO);
	command_tab = ft_split(argv[argc - 2], ' ');
	command_path = get_path(envp, command_tab[0]);
	if (command_path == NULL)
	{
		if (argv[argc - 2][0] == '/')
			perror(NULL);
		else
			write(STDERR_FILENO, "Command not found", 18);
		exit(127);
	}
	if (execve(command_path, command_tab, envp) == -1)
	{
		free_pipex(pipex);
		exit(EXIT_FAILURE);
	}
	free_pipex(pipex);
	exit(0);
}
