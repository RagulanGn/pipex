/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgnanaso <rgnanaso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 12:34:35 by rgnanaso          #+#    #+#             */
/*   Updated: 2024/04/23 14:52:56 by rgnanaso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	ft_count_str(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if ((s[i] != c && s[i + 1] == '\0') || (s[i] != c && s[i + 1] == c))
			count++;
		i++;
	}
	return (count);
}

char	**ft_clear(char **str_arr)
{
	int	i;

	i = 0;
	while (str_arr[i])
	{
		free(str_arr[i]);
		i++;
	}
	free(str_arr);
	return (NULL);
}

static size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size < 1)
		return (ft_strlen(src));
	while (i < size - 1 && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}

char	**ft_split(char const *s, char c)
{
	char	**str_arr;
	int		count;
	int		i;

	str_arr = malloc((ft_count_str(s, c) + 1) * sizeof(char *));
	if (str_arr == NULL)
		return (NULL);
	i = 0;
	while (*s)
	{
		count = 0;
		while (*s && *s == c)
			s++;
		if (!(*s))
			break ;
		while (*s && *s != c && s++)
			count++;
		str_arr[i] = malloc(count + 1);
		if (str_arr[i] == NULL)
			return (ft_clear(str_arr));
		ft_strlcpy(str_arr[i++], s - count, count + 1);
	}
	str_arr[i] = NULL;
	return (str_arr);
}
