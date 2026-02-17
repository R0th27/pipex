/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htoe <htoe@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 18:30:01 by htoe              #+#    #+#             */
/*   Updated: 2026/02/17 16:17:09 by htoe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_in_type	detect_input_type(const char *arg)
{
	if (!ft_strncmp(arg, "here_doc", 9))
		return (INPUT_HEREDOC);
	return (INPUT_FILE);
}

int	heredoc_read(int fd, const char *limiter)
{
	char	*line;
	size_t	len;

	len = ft_strlen(limiter) + 1;
	line = get_next_line(STDIN_FILENO);
	while (line && ft_strncmp(line, limiter, len) != '\n')
	{
		if (write(fd, line, ft_strlen(line)) == -1)
			return (free(line), 0);
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	free(line);
	return (1);
}
