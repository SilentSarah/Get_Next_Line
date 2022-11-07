/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeftah <hmeftah@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 19:04:48 by hmeftah           #+#    #+#             */
/*   Updated: 2022/11/07 20:46:12 by hmeftah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*cut_line(char *tempbuffer, char *line)
{
	int		i;
	char	*wantedline;

	i = 0;
	wantedline = NULL;
	if (!tempbuffer)
		return (NULL);
	if (line)
		free(line);
	while (tempbuffer[i] != '\n' && tempbuffer[i])
		i++;
	if (tempbuffer[i] == '\n')
		i++;
	wantedline = (char *)malloc(i + 1);
	if (!(wantedline))
	{
		free(tempbuffer);
		return (NULL);
	}
	i++;
	wantedline[--i] = '\0';
	while (i-- > 0)
		wantedline[i] = tempbuffer[i];
	return (wantedline);
}

char	*update_buffer(char *tempbuffer)
{
	char	*newbuffer;
	int		i;
	int		j;

	i = 0;
	j = 0;
	newbuffer = NULL;
	while (tempbuffer[i] != '\n' && tempbuffer[i])
		i++;
	if (tempbuffer[i] == '\n')
		i++;
	newbuffer = (char *)malloc(ft_strlen(tempbuffer) - i + 1);
	if (!(newbuffer))
	{
		free(tempbuffer);
		return (NULL);
	}
	while (tempbuffer[i] != '\0')
		newbuffer[j++] = tempbuffer[i++];
	newbuffer[j] = '\0';
	free(tempbuffer);
	return (newbuffer);
}

char	*read_and_update_tempbuffer(
	int fd, char *buffer, char *tempbuffer, char *line)
{
	int			bytesread;

	bytesread = 1;
	while (bytesread > 0 && !ft_lookforchar(tempbuffer, '\n'))
	{
		bytesread = read(fd, buffer, BUFFER_SIZE);
		if (bytesread == -1)
		{
			free (tempbuffer);
			tempbuffer = NULL;
			free (line);
			line = NULL;
			return (0);
		}
		buffer[bytesread] = '\0';
		tempbuffer = ft_joinstring(tempbuffer, buffer);
	}
	return (tempbuffer);
}

char	*get_next_line(int fd)
{
	char		buffer[BUFFER_SIZE + 1];
	static char	*tempbuffer;
	char		*line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	tempbuffer = read_and_update_tempbuffer(fd, buffer, tempbuffer, line);
	if (!(tempbuffer))
		return (0);
	if (tempbuffer[0] == '\0')
	{
		free (tempbuffer);
		tempbuffer = NULL;
		free (line);
		line = NULL;
		return (0);
	}
	line = cut_line(tempbuffer, line);
	tempbuffer = update_buffer(tempbuffer);
	return (line);
}
