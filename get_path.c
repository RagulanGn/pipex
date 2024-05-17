/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgnanaso <rgnanaso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 17:19:47 by rgnanaso          #+#    #+#             */
/*   Updated: 2024/05/17 17:41:30 by rgnanaso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_path(char *envp[], char *cmd)
{
	char	**tab_path;
	char	*cmd_path;
	char	*cmd_path2;
	int		i;

	i = 0;
	if (cmd == NULL)
		return (NULL);
	if (!access(cmd, F_OK))
	{
		if (access(cmd, X_OK))
			return (NULL);
		return (cmd);
	}
	if (envp[0] == NULL)
		return (NULL);
	while (ft_strncmp(envp[i], "PATH", 4))
		i++;
	if (envp[i] == NULL)
		return (NULL);
	tab_path = ft_split(envp[i] + 5, ':');
	i = -1;
	while (tab_path[++i])
	{
		cmd_path2 = ft_strjoin(tab_path[i], "/");
		cmd_path = ft_strjoin(cmd_path2, cmd);
		free(cmd_path2);
		if (!access(cmd_path, F_OK))
		{
			ft_clear(tab_path);
			return (cmd_path);
		}
		free(cmd_path);
	}
	ft_clear(tab_path);
	return (NULL);
}
