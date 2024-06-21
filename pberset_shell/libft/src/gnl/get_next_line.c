/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 15:04:46 by pberset           #+#    #+#             */
/*   Updated: 2024/03/18 15:14:10 by pberset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/get_next_line.h"

static char	*join_c(char *line_c, char *line_r)
{
	char	*tmp;

	tmp = ft_strjoin(line_c, line_r);
	if (!tmp)
	{
		free(line_c);
		return (NULL);
	}
	free(line_c);
	return (tmp);
}

static char	*read_file(int fd, char *line_c)
{
	char	*line_r;
	int		bytes_r;

	line_r = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!line_r)
		return (NULL);
	bytes_r = 1;
	while (bytes_r > 0 && !ft_strchr(line_c, '\n'))
	{
		bytes_r = read(fd, line_r, BUFFER_SIZE);
		if (bytes_r < 0)
		{
			free(line_r);
			free(line_c);
			return (NULL);
		}
		if (bytes_r == 0)
			break ;
		line_r[bytes_r] = '\0';
		line_c = join_c(line_c, line_r);
		if (!line_c)
			return (NULL);
	}
	free(line_r);
	return (line_c);
}

static char	*get_line(char *line_c)
{
	char	*output;
	int		i;

	if (!line_c)
		return (NULL);
	i = 0;
	while ((unsigned char)line_c[i] != '\0' && (unsigned char)line_c[i] != '\n')
		i++;
	output = (char *)malloc((i + 2) * sizeof(char));
	if (!output)
		return (NULL);
	i = 0;
	while ((unsigned char)line_c[i] != '\0' && (unsigned char)line_c[i] != '\n')
	{
		output[i] = (unsigned char)line_c[i];
		i++;
	}
	if ((unsigned char)line_c[i] == '\n')
	{
		output[i] = '\n';
		i++;
	}
	output[i] = '\0';
	return (output);
}

static char	*update_line_c(char	*line_c)
{
	char	*update;
	int		i;
	int		j;

	update = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!update)
	{
		if (line_c)
			free(line_c);
		return (NULL);
	}
	i = 0;
	while ((unsigned char)line_c[i] != '\0' && (unsigned char)line_c[i] != '\n')
		i++;
	if ((unsigned char)line_c[i] == '\n')
		i++;
	j = 0;
	while ((unsigned char)line_c[i] != '\0')
		update[j++] = (unsigned char)line_c[i++];
	update[j] = '\0';
	free(line_c);
	return (update);
}

char	*get_next_line(int fd)
{
	static char	*line_c[4096];
	char		*output;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line_c[fd] = read_file(fd, line_c[fd]);
	if (!line_c[fd])
		return (NULL);
	output = get_line(line_c[fd]);
	if (!output)
	{
		free(line_c[fd]);
		return (NULL);
	}
	line_c[fd] = update_line_c(line_c[fd]);
	if (!line_c[fd] || !(*(line_c[fd])))
	{
		free(line_c[fd]);
		line_c[fd] = NULL;
	}
	return (output);
}
