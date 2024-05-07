/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgnanaso <rgnanaso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 19:09:27 by marvin            #+#    #+#             */
/*   Updated: 2024/04/23 16:44:42 by rgnanaso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	has_new_line(char *buf)
{
	while (*buf)
	{
		if (*buf == '\n')
			return (1);
		buf++;
	}
	return (0);
}

void	*ft_clear_gnl(t_list *lst, char **buf)
{
	t_list	*lst_next;

	while (lst)
	{
		lst_next = (lst)->next;
		free((lst)->content);
		free(lst);
		lst = lst_next;
	}
	lst = NULL;
	if (buf == NULL)
		return (NULL);
	free(*buf);
	*buf = NULL;
	return (NULL);
}

char	*ft_strdup_newline(char *s)
{
	int		i;
	char	*str;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\n')
		i++;
	str = malloc (i + 1);
	if (str == NULL)
		return (0);
	i = 0;
	while (s[i] && s[i] != '\n')
	{
		str[i] = s[i];
		i++;
	}
	if (s[i] == '\n')
		str[i++] = '\n';
	str[i] = 0;
	return (str);
}

char	*ft_strcut(char *s)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\n')
		i++;
	while (s[i])
		s[j++] = s[i++];
	s[j] = 0;
	return (s);
}
