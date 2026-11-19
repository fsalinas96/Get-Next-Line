/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsalinas <fsalinas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 21:20:02 by fsalinas          #+#    #+#             */
/*   Updated: 2026/11/19 18:29:52 by fsalinas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	ft_read(int fd, char **stash, char *buffer)
{
	ssize_t	bytes;

	while (!ft_has_newline(*stash))
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
			return (-1);
		else if (bytes == 0)
			return (0);
		buffer[bytes] = '\0';
		if (ft_stash_update(stash, buffer) < 1)
			return (-1);
	}
	return (1);
}

char	*ft_line(char *stash)
{
	char	*line;
	int		position;
	int		i;

	position = 0;
	i = 0;
	if (stash && stash[0] != '\0')
	{
		while (stash[position] != '\n' && stash[position] != '\0')
			position++;
		if (stash[position] == '\n')
			position++;
		line = malloc((position + 1) * sizeof(char));
		if (!line)
			return (NULL);
		while (stash[i] && (i < position))
		{
			line[i] = stash[i];
			i++;
		}
		line[position] = '\0';
		return (line);
	}
	else
		return (NULL);
}

int	ft_new_stash(char **stash)
{
	char	*new_stash;
	int		from_here;

	from_here = 0;
	if (!stash || !(*stash))
		return (0);
	while ((*stash)[from_here] != '\n' && (*stash)[from_here] != '\0')
		from_here++;
	if ((*stash)[from_here] == '\0' || !(*stash)[from_here + 1])
	{
		free((*stash));
		(*stash) = NULL;
		return (1);
	}
	new_stash = ft_strdup(&(*stash)[from_here + 1]);
	if (!new_stash)
	{
		free((*stash));
		(*stash) = NULL;
		return (0);
	}
	free((*stash));
	(*stash) = new_stash;
	return (1);
}

void	*ft_free(char **stash, char *buffer)
{
	free (buffer);
	free (*stash);
	*stash = NULL;
	return (NULL);
}

char	*get_next_line(int fd)
{
	char		*line;
	int			reader;
	char		*buffer;
	static char	*stash[1024];

	if (fd < 0 || fd >= 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (ft_free(&stash[fd], buffer));
	reader = ft_read(fd, &stash[fd], buffer);
	if (reader == -1)
		return (ft_free(&stash[fd], buffer));
	if (stash[fd] == NULL || stash[fd][0] == '\0')
		return (ft_free(&stash[fd], buffer));
	line = ft_line(stash[fd]);
	if (line == NULL)
		return (ft_free(&stash[fd], buffer));
	free(buffer);
	if (!ft_new_stash(&(stash[fd])))
	{
		free(line);
		return (NULL);
	}
	return (line);
}
