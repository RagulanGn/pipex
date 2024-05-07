/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgnanaso <rgnanaso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:31:57 by rgnanaso          #+#    #+#             */
/*   Updated: 2024/05/07 15:17:48 by rgnanaso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_infile_outfile(t_pipex *pipex, char *argv[], int i)
{
	if (i == 0)
	{
		if (access(argv[1], R_OK))
		{
			perror(NULL);
			exit(0);
		}
		pipex->file[0] = open(argv[1], O_RDONLY);
		if (pipex->file[0] < 0)
		{
			perror(NULL);
			exit(0);
		}
		dup2(pipex->file[0], STDIN_FILENO);
	}
	else if (i == pipex->argc - 4) //change
	{
		if (!access(argv[pipex->argc - 1], F_OK) && access(argv[pipex->argc - 1], W_OK))
		{
			perror(NULL);
			exit(0);
		}
		if (pipex->file[1] < 0)
		{
			perror(NULL);
			exit(0);
		}
		dup2(pipex->file[1], STDOUT_FILENO);
	}
}

void	executer(t_pipex *pipex, char *envp[], char *argv[], int i)
{
	char	*command_path;
	char	**command_tab;
	int		fd[2];

	pipe(fd);
	pipex->pid = fork();
	if (pipex->pid < 0)
		exit(0);
	else if (pipex->pid == 0)
	{
		command_tab = ft_split(argv[i + 2], ' '); //Leak move into child reduce leak
		command_path = get_path(envp, command_tab[0]); // Leak
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		check_infile_outfile(pipex, argv, i);
		if (command_path == NULL)
		{
			if (argv[i + 2][0] == '/')
				perror(NULL);
			else
				write(STDERR_FILENO, "Command not found\n", 19);
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

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	*pipex;
	int		i;

	if (argc < 5)
		return (0);
	pipex = init_pipex(argv, argc);
	i = -1;
	pipex->file[1] = open(argv[pipex->argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	while (++i < argc - 3)
		executer(pipex, envp, argv, i);
}
