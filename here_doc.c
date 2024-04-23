/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgnanaso <rgnanaso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 17:40:10 by rgnanaso          #+#    #+#             */
/*   Updated: 2024/04/23 15:35:28 by rgnanaso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	here_doc(char *argv[])
{
	char	*line;
	int		fd;

	line = get_next_line(0);
	fd = open("here_docu", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	while (1)
	{
		if (!ft_strncmp(line, argv[2], ft_strlen(argv[2])))
			break ;
		write(fd, line, ft_strlen(line));
		line = get_next_line(0);
	}
	close(fd);
	return (0);
}
