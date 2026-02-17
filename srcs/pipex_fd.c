/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htoe <htoe@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 23:56:27 by htoe              #+#    #+#             */
/*   Updated: 2026/02/18 00:24:18 by htoe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	safe_dup(t_exec *exec, t_pipeline *pl)
{
	if (exec->i == 0)
		dup2(pl->infile, STDIN_FILENO);
	else
		dup2(exec->prev_fd, STDIN_FILENO);
	if (exec->i == (pl->cmd_counts - 1))
		dup2(pl->outfile, STDOUT_FILENO);
	else
		dup2(exec->pipefd[1], STDOUT_FILENO);
}

int	safe_pipe(t_exec *exec, int last)
{
	if (exec->i == last - 1)
		return (1);
	if (pipe(exec->pipefd) == -1)
		return (0);
	return (1);
}

static void	safe_close(int *fd)
{
	if (*fd >= 0)
		close(*fd);
	*fd = -1;
}

void	fd_closure(t_exec *exec, t_pipeline *pl, int cl_all)
{
	if (cl_all)
	{
		safe_close(&(exec->pipefd[0]));
		safe_close(&(pl->outfile));
		safe_close(&(pl->infile));
	}
	safe_close(&(exec->prev_fd));
	safe_close(&(exec->pipefd[1]));
}
