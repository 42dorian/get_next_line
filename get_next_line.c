/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabdulla <dabdulla@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 19:09:55 by dabdulla          #+#    #+#             */
/*   Updated: 2025/10/29 17:55:16 by dabdulla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*join_free(char *s1, char *s2)
{
	char	*tmp;

	tmp = ft_strjoin(s1, s2);
	if (!tmp)
		return (NULL);
	return (tmp);
}

int	find_new_line(char *str)
{
	int	i;

	i = 0;
	if (*str == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
			return (i + 1);
		i++;
	}
	return (i);
}

int	is_newline(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			return (i + 1);
		i++;
	}
	return (0);
}

char	*read_loop(int fd, char *file)
{
	char	*buffer;
	int		r;

	if (!file)
	{
		file = malloc(1);
		if (!file)
			return (NULL);
		file[0] = '\0';
	}
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (free(file), NULL);
	r = 1;
	while (r > 0 && !is_newline(file))
	{
		r = read(fd, buffer, BUFFER_SIZE);
		buffer[r] = '\0';
		file = join_free(file, buffer);
	}
	free(buffer);
	return (file);
}
int	check_fd(int fd,char *file)
{
	if(fd < 0 || read(fd, 0, 0) < 0 || BUFFER_SIZE <= 0)
	{
		return (0);
	}
	return (1);
}
char	*get_next_line(int fd)
{
	static char	*file;
	char		*tmp;
	char		*str;
	int			i;

	i = 0;
	if (!check_fd(fd, file))
		return (NULL);
	file = read_loop(fd, file);
	if (!file || *file == '\0')
		return (free(file), NULL);
	tmp = ft_substr(file, 0, find_new_line(file));
	if (!tmp)
		return (free(file), NULL);
	i = find_new_line(tmp) - ft_strlen(file);
	str = ft_substr(file, find_new_line(tmp), i);
	free(file);
	if (!str)
		return (free(str), free(tmp), NULL);
	file = NULL;
	file = ft_strdup(str);
	free(str);
	if (!file)
		return (free(file), free(tmp), NULL);
	return (tmp);
}

// #include "get_next_line_utils.c"
int	main(void)
{
	int fd;
	char *s;
	int i;

	i = 0;
	fd = open("test.txt", O_RDONLY);
	while ((s = get_next_line(fd)) && i < 10)
	{
		printf("%s", s);
		free(s);
		i++;
	}
	close(fd);
}