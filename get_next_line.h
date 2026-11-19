/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsalinas <fsalinas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/19 18:06:21 by fsalinas          #+#    #+#             */
/*   Updated: 2026/11/19 18:28:59 by fsalinas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

int		ft_read(int fd, char **stash, char *buffer);
char	*ft_line(char *stash);
int		ft_new_stash(char **stash);
void	*ft_free(char **stash, char *buffer);
char	*get_next_line(int fd);
size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *s);
void	ft_strcat(char *s1, char *s2, char *dest);
int		ft_stash_update(char **stash, char *buffer);
int		ft_has_newline(char *s);

#endif