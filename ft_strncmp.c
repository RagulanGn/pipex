/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgnanaso <rgnanaso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 17:41:13 by rgnanaso          #+#    #+#             */
/*   Updated: 2024/05/17 16:54:54 by rgnanaso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (s1 == NULL)
		return (0);
	if (n == 0)
		return (0);
	while ((unsigned char) s1[i] == (unsigned char) s2[i] && i < n - 1 && s1[i])
		i++;
	return ((unsigned char) s1[i] - (unsigned char) s2[i]);
}
