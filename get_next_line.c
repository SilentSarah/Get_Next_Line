/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeftah <hmeftah@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 19:04:48 by hmeftah           #+#    #+#             */
/*   Updated: 2022/11/07 20:27:22 by hmeftah          ###   ########.fr       */
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

// int	read_and_append_to_temp_buffer(
// 	int fd, char *buffer, char *tempbuffer, char *line)
// {
// 	int	bytesread;

// 	bytesread = read(fd, buffer, BUFFER_SIZE);
// 	if (bytesread == -1)
// 	{
// 		free (tempbuffer);
// 		tempbuffer = NULL;
// 		free (line);
// 		line = NULL;
// 		return (bytesread);
// 	}
// 	buffer[bytesread] = '\0';
// 	tempbuffer = ft_joinstring(tempbuffer, buffer);
// 	return (bytesread);
// }

char	*get_next_line(int fd)
{
	char		buffer[BUFFER_SIZE + 1];
	int			bytesread;
	static char	*tempbuffer;
	char		*line;

	bytesread = 1;
	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
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
	if (tempbuffer[0] == '\0')
	{
		free(tempbuffer);
		tempbuffer = NULL;
		return (0);
	}	
	line = cut_line(tempbuffer, line);
	tempbuffer = update_buffer(tempbuffer);
	return (line);
}
