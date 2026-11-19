/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsalinas <fsalinas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/19 16:01:00 by fsalinas          #+#    #+#             */
/*   Updated: 2026/11/19 18:29:13 by fsalinas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (*str)
	{
		i++;
		str++;
	}
	return (i);
}

char	*ft_strdup(const char *s)
{
	int		i;
	int		j;
	int		numitems;
	char	*dest;

	i = 0;
	j = 0;
	while (s[j])
		j++;
	numitems = j;
	dest = malloc ((numitems + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	while (s[i])
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void	ft_strcat(char *s1, char *s2, char *dest)
{
	int	i;

	i = 0;
	while (s1 && *s1)
	{
		dest[i] = *s1;
		s1++;
		i++;
	}
	while (*s2)
	{
		dest[i] = *s2;
		s2++;
		i++;
	}
	dest[i] = '\0';
}

int	ft_stash_update(char **stash, char *buffer)
{
	char	*updated;
	size_t	size;

	if (!stash || !buffer)
		return (0);
	size = ft_strlen(buffer) + 1;
	if (*stash)
		size = size + ft_strlen(*stash);
	updated = malloc(size);
	if (!updated)
		return (0);
	ft_strcat(*stash, buffer, updated);
	free(*stash);
	*stash = updated;
	return (1);
}

int	ft_has_newline(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}
