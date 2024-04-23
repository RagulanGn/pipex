/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgnanaso <rgnanaso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 19:09:37 by marvin            #+#    #+#             */
/*   Updated: 2024/04/23 14:26:20 by rgnanaso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "stdio.h"
# include "string.h"
# include "fcntl.h"
# include "unistd.h"
# include "stdlib.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}t_list;

char	*get_next_line(int fd);
char	*ft_join_list(t_list *list);
void	*ft_clear_gnl(t_list *lst, char **buf);
t_list	*ft_read(int fd, t_list *lst, t_list *start, char *buf);
char	*ft_strdup_newline(char *s);
int		has_new_line(char *buf);
size_t	ft_strlen(const char *s);
char	*ft_strcut(char *s);


#endif