/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgnanaso <rgnanaso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 19:08:40 by marvin            #+#    #+#             */
/*   Updated: 2024/04/23 14:27:42 by rgnanaso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*lst_new;

	lst_new = malloc(sizeof(t_list));
	if (lst_new == NULL)
		return (NULL);
	lst_new->content = content;
	lst_new->next = NULL;
	return (lst_new);
}

size_t	ft_strcat(char *dst, const char *src)
{
	size_t	i;
	size_t	dst_len;

	dst_len = ft_strlen(dst);
	i = 0;
	while (src[i])
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (dst_len + ft_strlen(src));
}

char	*ft_join_list(t_list *list)
{
	char	*result;
	int		len;
	t_list	*start;

	len = 0;
	start = list;
	while (list)
	{
		if (list->content)
			len += ft_strlen(list->content);
		list = list->next;
	}
	list = start;
	result = malloc(len + 1);
	if (result == NULL)
		return (NULL);
	result[0] = 0;
	while (list)
	{
		if (list->content)
			ft_strcat(result, list->content);
		list = list->next;
	}
	ft_clear_gnl(start, NULL);
	return (result);
}

char	*get_next_line(int fd)
{
	static char	*buf;
	t_list		*start;
	t_list		*lst;

	lst = ft_lstnew(NULL);
	start = lst;
	if (buf)
	{
		lst->content = ft_strdup_newline(buf);
		buf = ft_strcut(buf);
		if (ft_strlen(buf) != 0)
			return (ft_join_list(start));
		lst->next = ft_lstnew(NULL);
		lst = lst->next;
	}
	else
		buf = malloc(BUFFER_SIZE + 1);
	if (ft_read(fd, lst, start, buf) == NULL)
		return (ft_clear_gnl(start, &buf));
	return (ft_join_list(start));
}

t_list	*ft_read(int fd, t_list *lst, t_list *start, char *buf)
{
	int	read_value;

	read_value = read(fd, buf, BUFFER_SIZE);
	if (read_value == 0 && start->content && ft_strlen(start->content))
		return (start);
	if (read_value <= 0)
		return (NULL);
	buf[read_value] = 0;
	lst->content = ft_strdup_newline(buf);
	while (!has_new_line(buf) && read_value)
	{
		buf = ft_strcut(buf);
		read_value = read(fd, buf, BUFFER_SIZE);
		if (read_value < 0)
			return (ft_clear_gnl(start, &buf));
		buf[read_value] = 0;
		lst->next = ft_lstnew(ft_strdup_newline(buf));
		lst = lst->next;
	}
	buf = ft_strcut(buf);

	return (lst);
}
