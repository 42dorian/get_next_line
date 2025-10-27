/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabdulla <dabdulla@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 19:09:55 by dabdulla          #+#    #+#             */
/*   Updated: 2025/10/27 22:13:02 by dabdulla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
// #include "get_next_line_utils.c"
#include <stdio.h>

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*str;

	str = (unsigned char *)s;
	while (n--)
		*str++ = c;
	return (s);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (nmemb == 0 || size == 0)
	{
		ptr = malloc(0);
		if (!ptr)
			return (NULL);
		return (ptr);
	}
	if (nmemb > (size_t)-1 / size)
		return (NULL);
	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	ft_memset(ptr, 0, nmemb * size);
	return (ptr);
}

int	is_newline(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != 0)
	{
		if (s[i] == '\n')
			return (i + 1);
		i++;
	}
	return (0);
}

// char	*read_buffer(char *buffer, char *file)
// {
// 	int		i;
// 	char	*tmp;

// 	if (file != NULL)
// 	{
// 		tmp = ft_strjoin(file, buffer);
// 		return (free(file), free(buffer), tmp);
// 	}
// 	file = ft_calloc(ft_strlen(buffer) + 1, sizeof(char));
// 	i = 0;
// 	while (buffer[i])
// 	{
// 		if (buffer[i] == '\n')
// 		{
// 			file[i] = buffer[i];
// 			// ft_memset((char *))
// 			return (file);
// 		}
// 		file[i] = buffer[i];
// 		i++;
// 	}
// 	file[i] = '\0';
// 	return (free(buffer), file);
// }

char	*read_buffer(char *buffer, char *file)
{
	char	*tmp;

	if (!file)
		return (ft_strdup(buffer));
	tmp = ft_strjoin(file, buffer);
	free(file);
	return (tmp);
}

char	*get_next_line(int fd)
{
	static char	*file;
	char		*buffer;
	char		*line;
	int			r;
	char		*tmp;

	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	r = 1;
	while (r > 0 && !is_newline(file))
	{
		r = read(fd, buffer, BUFFER_SIZE);
		if (r <= 0)
			break ;
		buffer[r] = '\0';
		file = read_buffer(buffer, file);
	}
	free(buffer);
	if (!file || *file == '\0')
		return (free(file), file = NULL, NULL);
	r = is_newline(file);
	if (r)
	{
		line = ft_substr(file, 0, r);
		tmp = ft_strdup(file + r);
		free(file);
		file = tmp;
		return (line);
	}
	line = ft_strdup(file);
	free(file);
	file = NULL;
	return (line);
}

int	main(void)
{
	int fd;
	char *s;
	
	fd = open("test.txt", O_RDONLY);
	while ((s = get_next_line(fd)))
	{
		printf("%s", s);
		free(s);
	}

	close(fd);
}