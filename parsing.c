/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgnanaso <rgnanaso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 14:35:23 by rgnanaso          #+#    #+#             */
/*   Updated: 2024/04/23 15:41:53 by rgnanaso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_pipex(t_pipex *pipex)
{
	int	i;

	i = -1;
	if (pipex->command != NULL)
	{
		while (pipex->command[++i])
			ft_clear(pipex->command[i]);
		free(pipex->command);
	}
	if (pipex->command_path != NULL)
		ft_clear(pipex->command_path);
	if (pipex->file[0] > 0)
		close(pipex->file[0]);
	if (pipex->file[1] > 0)
		close(pipex->file[1]);
	free(pipex);
}

t_pipex	*init_pipex(int argc, char *argv[])
{
	t_pipex	*pipex;
	int		i;

	i = 1;
	pipex = malloc(sizeof(t_pipex));
	if (pipex == NULL)
		return (NULL);
	pipex->command = malloc(sizeof(char **) * argc - 2);
	if (pipex->command == NULL)
	{
		free_pipex(pipex);
		return (NULL);
	}
	pipex->command_path = malloc(sizeof(char *) * argc - 2);
	if (pipex->command_path == NULL)
	{
		free_pipex(pipex);
		return (NULL);
	}
	pipex->here_doc = 0;
	if (!ft_strncmp(argv[1], "here_doc", 8))
		pipex->here_doc = 1;
	return (pipex);
}

t_pipex	*parsing(t_pipex *pipex, int argc, char *argv[], char *envp[])
{
	int		i;

	i = 1;
	while (++i < argc - 1 - pipex->here_doc)
		pipex->command[i - 2] = ft_split(argv[i + pipex->here_doc], ' ');
	pipex->command[i - 2] = NULL;
	i = -1;
	while (pipex->command[++i])
	{
		pipex->command_path[i] = get_path(envp, pipex->command[i][0]);
		if (pipex->command_path[i] == NULL)
		{
			free_pipex(pipex);
			exit(errno);
		}
	}
	pipex->command_path[i] = NULL;
	pipex->file[0] = open(argv[1], O_RDONLY);
	if (pipex->here_doc)
		pipex->file[1] = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0666); //Replace O_WRONLY by 01
	else
	{
		pipex->file[0] = open(argv[1], O_RDONLY);
		pipex->file[1] = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	}
	if ((pipex->file[0] < 0  && !pipex->here_doc) || pipex->file[1] < 0)
	{
		free_pipex(pipex);
		return (NULL);
	}
	return (pipex);
}
