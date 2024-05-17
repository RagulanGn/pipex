/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgnanaso <rgnanaso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:31:57 by rgnanaso          #+#    #+#             */
/*   Updated: 2024/05/17 18:08:50 by rgnanaso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_gest(int exit_code, t_pipex *pipex) // char *msg
{
	perror(NULL);
	//if (msg != NULL)
	//	write(STDERR_FILENO, msg, ft_strlen(msg));
	free_pipex(pipex);
	exit(exit_code);
}

void	check_infile_outfile(t_pipex *pipex, char *argv[], int i)
{
	if (i == 0)
	{
		if (access(argv[1], R_OK))
			error_gest(1, pipex);
		if (pipex->file[0] < 0)
			error_gest(1, pipex);
		dup2(pipex->file[0], STDIN_FILENO);
	}
	else if (i == pipex->argc - 4) //change
	{
		if (!access(argv[pipex->argc - 1], F_OK) && access(argv[pipex->argc - 1], W_OK))
			error_gest(1, pipex);
		if (pipex->file[1] < 0)
			error_gest(1, pipex);
		dup2(pipex->file[1], STDOUT_FILENO);
	}
	close(pipex->file[0]);
	close(pipex->file[1]);
}

void	executeyes(t_pipex *pipex, char *envp[], char *argv[], int i)
{
	char	*command_path;
	char	**command_tab;

	command_tab = ft_split(argv[i + 2], ' '); //Leak move into child reduce leak
	command_path = get_path(envp, command_tab[0]); // Leak
	if (command_path == NULL)
	{
		free_pipex(pipex);
		if (command_tab[0] && !access(command_tab[0], F_OK) && access(command_tab[0], X_OK))
		{
			ft_clear(command_tab);
			command_tab = NULL;
			perror(NULL);
			exit(126);
		}
		if (argv[i + 2][0] == '/')
			perror(NULL);
		else
		{
			write(STDERR_FILENO, "Command not found:", 18);
			if (command_tab[0])
				write(STDERR_FILENO, command_tab[0], ft_strlen(command_tab[0]));
			write(STDERR_FILENO, "\n", 1);
		}
		ft_clear(command_tab);
		command_tab = NULL;
		exit(127);
	}
	if (execve(command_path, command_tab, envp) == -1) //here
	{
		free_pipex(pipex);
		exit(EXIT_FAILURE);
	}
}

void	executer(t_pipex *pipex, char *envp[], char *argv[], int i)
{
	int	pip[2];

	pipe(pip);
	pipex->pid = fork();
	if (pipex->pid < 0)
		exit(0);
	else if (pipex->pid == 0)
	{
		close(pip[0]);
		dup2(pip[1], STDOUT_FILENO);
		close(pip[1]);
		check_infile_outfile(pipex, argv, i);
		executeyes(pipex, envp, argv, i);
	}
	else
	{
		close(pip[1]);
		dup2(pip[0], STDIN_FILENO);
		close(pip[0]);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	*pipex;
	int		i;
	int		status;
	int		return_val;
	pid_t	pid;

	if (argc < 5)
		return (0);
	pipex = init_pipex(argv, argc);
	i = -1;
	pipex->file[0] = open(argv[1], O_RDONLY);
	pipex->file[1] = open(argv[pipex->argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	//pipe(pipex->pip);
	while (++i < argc - 3)
		executer(pipex, envp, argv, i);
	pid = waitpid(-1, &status, 0);
	while (pid > 0)
	{
		if (pipex->pid == pid)
			return_val = WEXITSTATUS(status);
		pid = waitpid(-1, &status, 0);
	}
	free_pipex(pipex);
	return (return_val);
}
