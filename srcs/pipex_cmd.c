/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htoe <htoe@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 00:27:19 by htoe              #+#    #+#             */
/*   Updated: 2026/02/18 00:37:48 by htoe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	exec_cmd(t_cmd cmd, char **envp)
{
	int	i;
	int	saw_eacces;
	int	saved_errno;

	saw_eacces = 0;
	saved_errno = 0;
	i = 0;
	if (!cmd.paths || !cmd.argv)
		return (error_cmd_not_found("hi"), ENOENT);
	while (cmd.paths[i])
	{
		execve(cmd.paths[i], cmd.argv, envp);
		if (errno == EACCES)
			saw_eacces = 1;
		else if (errno != ENOENT && !saved_errno)
			saved_errno = errno;
		i++;
	}
	if (i == 1 && errno == ENOENT)
		return (error_perror(cmd.argv[0]), errno);
	if (!saved_errno && !saw_eacces)
		return (error_cmd_not_found(cmd.argv[0]), ENOENT);
	if (saw_eacces)
		errno = EACCES;
	else if (saved_errno)
		errno = saved_errno;
	return (error_perror(cmd.argv[0]), errno);
}
