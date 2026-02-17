/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htoe <htoe@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 23:56:27 by htoe              #+#    #+#             */
/*   Updated: 2026/02/18 04:41:32 by htoe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	safe_dup(t_exec *exec, t_pipeline *pl)
{
	int	in_fd;
	int	out_fd;

	if (exec->i == 0)
		in_fd = pl->infile;
	else
		in_fd = exec->prev_fd;
	if (dup2(in_fd, STDIN_FILENO) == -1)
		return (0);
	if (exec->i == (pl->cmd_counts - 1))
	{
		if (pl->outfile < 0)
			return (0);
		out_fd = pl->outfile;
	}
	else
		out_fd = exec->pipefd[1];
	if (dup2(out_fd, STDOUT_FILENO) == -1)
		return (0);
	return (1);
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
