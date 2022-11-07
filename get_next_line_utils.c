/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeftah <hmeftah@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 19:04:54 by hmeftah           #+#    #+#             */
/*   Updated: 2022/11/07 20:46:24 by hmeftah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_lookforchar(char *str, char c)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (NULL);
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return ((str + i));
		else if (str[i] == '\0')
			return (NULL);
		i++;
	}
	return (NULL);
}

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*string;

	i = 0;
	string = (char *)malloc(sizeof(char) * ft_strlen(s1) + 1);
	if (!(string))
		return (NULL);
	while (s1[i])
	{
		string[i] = s1[i];
		i++;
	}
	string[i] = '\0';
	return (string);
}

char	*ft_joinstring(char *updatedbuffer, char *originalbuffer)
{
	char	*newstring;
	int		i;
	int		j;

	i = 0;
	j = 0;
	newstring = NULL;
	if (!updatedbuffer)
		updatedbuffer = ft_strdup("");
	newstring = (char *)malloc(
			ft_strlen(updatedbuffer) + ft_strlen(originalbuffer) + 1);
	if (!newstring)
	{
		free(updatedbuffer);
		return (NULL);
	}
	while (updatedbuffer[j] != '\0')
		newstring[i++] = updatedbuffer[j++];
	j = 0;
	while (originalbuffer[j] != '\0')
		newstring[i++] = originalbuffer[j++];
	newstring[i] = '\0';
	free(updatedbuffer);
	return (newstring);
}
