/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgnanaso <rgnanaso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 17:19:47 by rgnanaso          #+#    #+#             */
/*   Updated: 2024/03/19 15:20:24 by rgnanaso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_path(char *envp[], char *cmd)
{
	char	**tab_path;
	char	*cmd_path;
	int		i;

	i = 0;
	while (ft_strncmp(envp[i], "PATH", 4))
		i++;
	tab_path = ft_split(envp[i] + 5, ':');
	i = -1;
	while (tab_path[++i])
	{
		cmd_path = ft_strjoin(ft_strjoin(tab_path[i], "/"), cmd);
		if (!access(cmd_path, F_OK))
		{
			ft_clear(tab_path);
			return (cmd_path);
		}
	}
	ft_clear(tab_path);
	free(cmd_path);
	return (NULL); //Exit with correct error
}
