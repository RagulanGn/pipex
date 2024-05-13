/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_1305test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgnanaso <rgnanaso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:31:57 by rgnanaso          #+#    #+#             */
/*   Updated: 2024/05/13 16:01:25 by rgnanaso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_gest(int exit_code, t_pipex *pipex) // char *msg
{
	perror(NULL);
	// write(STDERR_FILENO, msg, ft_strlen(msg));
	free_pipex(pipex);
	exit(exit_code);
}

void	child(t_pipex *pipex, char *envp[], char *argv[])
{
	char	*command_path;
	char	**command_tab;

	close(pipex->pip[0]);
	dup2(pipex->file[0], STDIN_FILENO);
	dup2(pipex->pip[1], STDOUT_FILENO);

	command_tab = ft_split(argv[2], ' ');
	command_path = get_path(envp, command_tab[0]);
	if (command_path == NULL)
	{
		if (argv[2][0] == '/')
			perror(NULL);
		else
			write(STDERR_FILENO, "Command not found\n", 19);
		free_pipex(pipex);
		exit(127);
	}
	if (execve(command_path, command_tab, envp) == -1)
	{
		free_pipex(pipex);
		exit(EXIT_FAILURE);
	}
}

void	parent(t_pipex *pipex, char *envp[], char *argv[])
{
	char	*command_path;
	char	**command_tab;

	dup2(pipex->file[1], STDOUT_FILENO);
	close(pipex->pip[1]);
	dup2(pipex->pip[0], STDIN_FILENO);

	command_tab = ft_split(argv[3], ' ');
	command_path = get_path(envp, command_tab[0]);
	if (command_path == NULL)
	{
		if (argv[3][0] == '/')
			perror(NULL);
		else
			write(STDERR_FILENO, "Command not found\n", 19);
		free_pipex(pipex);
		exit(127);
	}
	if (execve(command_path, command_tab, envp) == -1)
	{
		free_pipex(pipex);
		exit(EXIT_FAILURE);
	}
}

void	wait_cmds(void)
{
	int		child_status;
	pid_t	ret;

	ret = 0;
	while (ret != -1)
	{
		ret = waitpid(-1, &child_status, 0);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	*pipex;
	int		i;
	// int		status;
	// int		return_val;

	if (argc < 5)
		return (0);
	pipex = init_pipex(argv, argc);
	i = -1;
	pipex->file[0] = open(argv[1], O_RDONLY);
	pipex->file[1] = open(argv[pipex->argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	pipe(pipex->pip);
	pipex->pid = fork();
	if (pipex->pid < 0)
		exit(0);
	else if (pipex->pid == 0)
		child(pipex, envp, argv);
	parent(pipex, envp, argv);

	wait_cmds();
	/* return_val = 0;
	waitpid(pipex->pid, &status, 0);
	return_val = WEXITSTATUS(status);
	while (wait(&status) > 0);
	free_pipex(pipex); */
	return (0);
}
