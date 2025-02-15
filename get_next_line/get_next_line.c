/*Assignment name : get_next_line
Expected files : get_next_line.c (42_EXAM can't take .h for now)
Allowed functions: read, free, malloc
--------------------------------------------------------------------------------

Write a function named get_next_line which prototype should be:
char *get_next_line(int fd);


Your function must return a line that has been read from the file descriptor passed as parameter. What we call a "line that has been read" is a succession of 0 to n characters that end with '\n' (ascii code 0x0a) or with End Of File (EOF).

The line should be returned including the '\n' in case there is one at the end of the line that has been read. When you've reached the EOF, you must store the current buffer in a char * and return it. If the buffer is empty you must return NULL.

In case of error return NULL. In case of not returning NULL, the pointer should be free-able. Your program will be compiled with the flag -D BUFFER_SIZE=xx, which has to be used as the buffer size for the read calls in your functions.

Your function must be memory leak free. When you've reached the EOF, your function should keep 0 memory allocated with malloc, except the line that has been returned.

Calling your function get_next_line() in a loop will therefore allow you to read the text available on a file descriptor one line at a time until the end of the text, no matter the size of either the text or one of its lines.

Make sure that your function behaves well when it reads from a file, from the standard output, from a redirection, etc...

No call to another function will be done on the file descriptor between 2 calls of get_next_line(). Finally we consider that get_next_line() has an undefined behaviour when reading from a binary file.*/



#include "get_next_line.h"

int	ft_strlen(char *str)
{
	int i = 0;

	while (str[i])
		i++;
	return (i);
}

char	*ft_strchr(char c, char *str)
{
	while (*str)
	{
		if (*str == c)
			return (str);
		str++;
	}
	return (NULL);
}

void	*ft_strcopy(char *dst, char *src)
{
	int i = 0;

	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
  return ;
}

char	*ft_strdup(char *str)
{
	char *new;

	new = malloc(sizeof(char) * ft_strlen(str) + 1);
	if (new == NULL)
		return (NULL);
	ft_strcopy(new, str);
	return (new);
}

char	*ft_strjoin(char *strOne, char *strTwo)
{
	char *new = malloc(sizeof(char) * (ft_strlen(strOne) + ft_strlen(strTwo)) + 1);

	if (!strOne || !strTwo || !new)
		return (NULL);
	ft_strcopy(new, strOne);
	ft_strcopy((new + ft_strlen(strOne)), strTwo);
	free(strOne);
	return (new);
}

char *get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	char	*line;
	char	*newline;
	int		countread;
	int		to_copy;

	line = ft_strdup(buf);
	while (!(newline = ft_strchr('\n', line))
				&& (countread = read(fd, buf, BUFFER_SIZE)))
	{
		buf[countread] = '\0';
		line = ft_strjoin(line, buf);
	}
	if (ft_strlen(line) == 0)
	{
		free(line);
		return (NULL);
	}
	if (newline != NULL)
	{
		to_copy = newline - line + 1;
		ft_strcopy(buf, newline + 1);
	}
	else
	{
		to_copy = ft_strlen(line);
		buf[0] = '\0';
	}
	line[to_copy] = '\0';
	return (line);
}

// int main(int argc, char **argv)
// {
//     int fd;
//     char *line;

//     if (argc != 2) 
//     {
//         printf("Usage: %s <filename>\n", argv[0]);
//         return 1;
//     }

//     fd = open(argv[1], O_RDONLY);
//     if (fd == -1) 
//     {
//         perror("Error opening file");
//         return 1;
//     }

//     while ((line = get_next_line(fd)) != NULL) 
//     {
//         printf("%s", line);
//         free(line);
//     }

//     close(fd);
//     return 0;
// }
