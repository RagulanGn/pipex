/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgnanaso <rgnanaso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 16:08:03 by rgnanaso          #+#    #+#             */
/*   Updated: 2024/02/19 18:10:11 by rgnanaso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	first_command(char *infile, char *command_path, char **tab)
{
	int		fd[2];
	int		infilefd;
	pid_t	pid;

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
		execve(command_path, tab, NULL);
	}
	else
	{
		char	buf[256];

		read(fd[0], buf, 255);
		printf("%s", buf);
		infilefd = open(infile, O_RDWR);
		write(infilefd, buf, 255);
		close(infilefd);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	char	command_path[256];
	char	*args[2];
	char	**tab;

	get_path(argv[2], command_path);
	rm_newline(command_path);
	tab = ft_split(argv[2], ' ', argv[1]);
	first_command(argv[1], command_path, tab);
	return (0);
}

/*
	Find where the command
	PID = Processus IDentifier
	PID = 0 => child 
	type command for finding the path (-p for ignoring alias)
	pipe used to create a channel between two process
	./pipex file1 command1 command2 file2

	first open file1
	create a binary script with command1

*/