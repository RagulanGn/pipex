/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgnanaso <rgnanaso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 16:08:03 by rgnanaso          #+#    #+#             */
/*   Updated: 2024/02/29 15:29:57 by rgnanaso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	first_command(char *outfile, char *command_path, char **tab)
{
	int		fd[2];
	int		outfilefd;
	pid_t	pid;
	char	buf[256];

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
		read(fd[0], buf, 255);
		//printf("%s", buf);
		outfilefd = open(outfile, 02);
		write(outfilefd, buf, ft_strlen(buf) - 1); // -1 cuz of the \n added
		close(outfilefd);
	}
	return (0);
}

void	child_process(char *argv[], char *envp[], int pip[2])
{
	char	**tab;
	char	command_path[256];

	tab = ft_split(argv[2], ' ');
	get_path(tab[0], command_path);
	rm_newline(command_path);
	dup2(pip[1], 1);
	execve(command_path, tab, envp);

}

void	parent_process(char *argv[], char *envp[], int pip[2])
{
	char	**tab;
	char	command_path[256];
	char	buf[256];

	read(pip[0], buf, 256);
	tab = ft_split(argv[3], ' ');
	get_path(tab[0], command_path);
	rm_newline(command_path);
	execve(command_path, tab, envp);
}


int	main(int argc, char *argv[], char *envp[])
{
	int		fd1;
	int		fd2;
	int		pip[2];
	pid_t	pid;

	fd1 = open(argv[1], O_RDONLY); //Check if it s a file first
	fd2 = open(argv[4], O_RDWR);
	dup2(fd1, STDIN_FILENO);
	dup2(fd2, STDOUT_FILENO);

	pipe(pip);
	pid = fork();
	if (pid < 0)
		return (0); //ERROR
	else if (pid == 0)
		child_process(argv, envp, pip);
	else
		parent_process(argv, envp, pip);
}

/* int	main(int argc, char *argv[], char *envp[])
{
	char	command_path[256];
	char	*args[2];
	char	**tab;

	tab = ft_split(argv[2], ' ', argv[1]);
	get_path(tab[0], command_path);
	rm_newline(command_path);
	first_command(argv[4], command_path, tab);
	tab = ft_split(argv[3], ' ', argv[4]);
	get_path(tab[0], command_path);
	rm_newline(command_path);
	second_command(argv[4], command_path, tab);
	return (0);
} */

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