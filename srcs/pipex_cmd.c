/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htoe <htoe@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 00:27:19 by htoe              #+#    #+#             */
/*   Updated: 2026/02/18 04:01:27 by htoe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	exec_init_check(t_cmd cmd)
{
	if (!cmd.argv || !cmd.argv[0])
		return (error_cmd_not_found(""), 0);
	if (!cmd.paths || !cmd.argv[0])
		return (error_cmd_not_found(cmd.argv[0]), 0);
	return (1);
}

int	exec_cmd(t_cmd cmd, char **envp)
{
	int	i;
	int	saw_eacces;
	int	first_error;

	if (!exec_init_check(cmd))
		return (ENOENT);
	saw_eacces = 0;
	first_error = 0;
	i = -1;
	while (cmd.paths[++i])
	{
		execve(cmd.paths[i], cmd.argv, envp);
		if (errno == EACCES)
			saw_eacces = 1;
		else if (errno != ENOENT && !first_error)
			first_error = errno;
	}
	if (i == 1 && errno == ENOENT)
		return (error_perror(cmd.argv[0]), ENOENT);
	if (saw_eacces)
		return (error_perror(cmd.argv[0]), EACCES);
	if (first_error)
		return (error_perror(cmd.argv[0]), first_error);
	return (error_cmd_not_found(cmd.argv[0]), ENOENT);
}
