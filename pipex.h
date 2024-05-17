/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgnanaso <rgnanaso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 16:08:08 by rgnanaso          #+#    #+#             */
/*   Updated: 2024/05/17 15:46:50 by rgnanaso         ###   ########.fr       */
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
# include <errno.h>
# include "get_next_line.h"

typedef struct s_pipex //Only for nbonus for now
{
	int		file[2];
	int		argc;
	int		pip[2];
	int		here_doc;
	pid_t	pid;
}	t_pipex;

void	free_pipex(t_pipex *pipex);
t_pipex	*init_pipex(char *argv[], int argc);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);

char	*get_path(char *envp[], char *cmd);

size_t	ft_strlen(const char *s);

char	**ft_clear(char **str_arr);
char	**ft_split(char const *s, char c);

int		here_doc(char *argv[]);


#endif