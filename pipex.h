/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgnanaso <rgnanaso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 16:08:08 by rgnanaso          #+#    #+#             */
/*   Updated: 2024/03/20 14:22:09 by rgnanaso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <unistd.h>
# include <sys/types.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_pipex //Only for nbonus for now
{
	char	***command;
	char	**command_path;
	int		file[2];
	int		pip[2];
}	t_pipex;

t_pipex	*init_pipex(int argc, char *argv[]);
t_pipex	*parsing(t_pipex *pipex, int argc, char *argv[], char *envp[]);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);

char	*get_path(char *envp[], char *cmd);

size_t	ft_strlen(const char *s);

char	**ft_clear(char **str_arr);
char	**ft_split(char const *s, char c);

int	execute(t_pipex *pipex, char *argv[], int argc);
int	exec_last(t_pipex *pipex, char *argv[], int argc);
int	exec_first(t_pipex *pipex);


#endif