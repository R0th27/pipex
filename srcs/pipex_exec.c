/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htoe <htoe@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 18:54:02 by htoe              #+#    #+#             */
/*   Updated: 2026/02/18 04:51:00 by htoe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	init_exec(t_exec *exec)
{
	exec->i = -1;
	exec->status = 0;
	exec->last_pid = 0;
	exec->pid = 0;
	exec->prev_fd = -1;
	exec->pipefd[0] = -1;
	exec->pipefd[1] = -1;
}

static void	wait_all_child(t_exec *exec)
{
	int	wpid;
	int	status;

	status = 0;
	while (true)
	{
		wpid = wait(&status);
		if (wpid == exec->last_pid)
			exec->status = status;
		if (wpid <= 0)
			break ;
	}
}

static void	exec_engine(t_pipeline **pl, t_exec *exec)
{
	int	saved_errno;

	if (!safe_dup(exec, *pl))
	{
		fd_closure(exec, *pl, 1);
		pipeline_destroy(pl);
		exit(1);
	}
	fd_closure(exec, *pl, 1);
	saved_errno = exec_cmd((*pl)->cmds[exec->i], (*pl)->envp);
	pipeline_destroy(pl);
	exit(error_code_from_errno(saved_errno));
}

int	pipeline_exec(t_pipeline **pl)
{
	t_exec	exec;

	init_exec(&exec);
	while (++(exec.i) < (*pl)->cmd_counts)
	{
		if (safe_pipe(&exec, (*pl)->cmd_counts) == -1)
			return (error_perror("pipe"), 1);
		exec.pid = fork();
		if (exec.pid == -1)
			return (error_perror("fork"), 1);
		if (exec.pid == 0)
			exec_engine(pl, &exec);
		if (exec.i + 1 == (*pl)->cmd_counts)
			exec.last_pid = exec.pid;
		fd_closure(&exec, *pl, 0);
		exec.prev_fd = exec.pipefd[0];
	}
	return (wait_all_child(&exec), exec.status >> 8);
}
