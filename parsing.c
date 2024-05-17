/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgnanaso <rgnanaso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 14:35:23 by rgnanaso          #+#    #+#             */
/*   Updated: 2024/05/17 17:51:05 by rgnanaso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_pipex(t_pipex *pipex)
{
	if (pipex->file[0] > 0)
		close(pipex->file[0]);
	if (pipex->file[1] > 0)
		close(pipex->file[1]);
	free(pipex);
}

t_pipex	*init_pipex(char *argv[], int argc)
{
	t_pipex	*pipex;
	int		i;

	i = 1;
	pipex = malloc(sizeof(t_pipex));
	if (pipex == NULL)
		return (NULL); //change to exit
	pipex->here_doc = 0;
	if (!ft_strncmp(argv[1], "here_doc", 8))
		pipex->here_doc = 1;
	pipex->argc = argc;
	return (pipex);
}
