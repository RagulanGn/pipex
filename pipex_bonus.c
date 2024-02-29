/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgnanaso <rgnanaso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 17:39:52 by rgnanaso          #+#    #+#             */
/*   Updated: 2024/02/29 18:18:14 by rgnanaso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "pipex.h"


void	child(int argc, char *argv[], char *envp[], int fd[2])
{
	int		fdin;
	char	**arg;
	char	*path;
	pid_t	pid;

	if (--argc > 0)
	{
		pid = fork();
		if (pid < 0)
			return; //error
		else if (pid == 0) //child
		{
			if (argc == 1)
			{
				fdin = open(argv[argc - 1], O_RDONLY);
				dup2(fdin, STDIN_FILENO);
				dup2(fd[1], STDOUT_FILENO);
				close(fd[0]);
				arg = ft_split(argv[2], ' ');
				path = get_path(arg[0]);
				rm_newline(path);
				execve("/bin/grep", arg, envp);
			}
			child(argc, argv, envp, fd);
		}
		else //Parent
		{
			fdin = open(argv[argc - 1], O_RDONLY);
			dup2(fdin, STDIN_FILENO);
			dup2(fd[1], STDOUT_FILENO);
			close(fd[0]);
			arg = ft_split(argv[2], ' ');
			path = get_path(arg[0]);
			rm_newline(path);
			execve("/bin/grep", arg, envp);
		}
	}
	else //First Child
	{
		fdin = open(argv[1], O_RDONLY);
		dup2(fdin, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		arg = ft_split(argv[2], ' ');
		path = get_path(arg[0]);
		rm_newline(path);
		execve("/bin/grep", arg, envp);
	}
}

void	parent(char *argv[], char *envp[], int fd[2])
{
	int		fdout;
	char	**arg;
	char	*path;

	fdout = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC);
	dup2(fdout, STDOUT_FILENO);
	dup2(fd[0], STDIN_FILENO);
	close(fd[1]);
	arg = ft_split(argv[3], ' ');
	path = get_path(arg[0]);
	rm_newline(path);
	execve("/usr/bin/wc", arg, envp);
}

int	main(int argc, char *argv[], char *envp[])
{
	int		fd[2];
	pid_t	pid;

	pipe(fd);
	pid = fork();
	if (pid < 0)
		return (0);
	else if (pid == 0)
		child(argc, argv, envp, fd);
	else
	{
		wait(NULL);
		parent(argv, envp, fd);
	}
}