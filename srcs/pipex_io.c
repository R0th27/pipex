/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_io.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htoe <htoe@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 06:05:31 by htoe              #+#    #+#             */
/*   Updated: 2026/02/08 08:19:24 by htoe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_io.h"

int	open_infile(const char *path)
{
	return (open(path, O_RDONLY));
}

int	open_outfile(const char *path, int append)
{
	if (append)
		return (open(path, O_CREAT | O_WRONLY | O_APPEND, 0644));
	else
		return (open(path, O_CREAT | O_WRONLY | O_TRUNC, 0644));
}

int	setup_input_fd(t_input_type type, const char *arg)
{
	if (type == INPUT_HEREDOC)
		return (heredoc_read(arg));
	return (open_infile(arg));
}

int	setup_output_fd(t_input_type type, const char *arg)
{
	if (type == INPUT_HEREDOC)
		return (open_outfile(arg, 1));
	return (open_outfile(arg, 0));
}

int	heredoc_read(const char *limiter)
{
	int		fd;
	char	*line;
	size_t	len;

	fd = open("pipex_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (-1);
	len = ft_strlen(limiter) + 1;
	line = get_next_line(STDIN_FILENO);
	while (line && ft_strncmp(line, limiter, len) != '\n')
	{
		if (write(fd, line, ft_strlen(line)) == -1)
			return (free(line), close(fd), -1);
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	free(line);
	close(fd);
	fd = open("pipex_tmp", O_RDONLY);
	return (fd);
}
