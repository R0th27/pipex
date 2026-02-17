/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htoe <htoe@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 18:54:02 by htoe              #+#    #+#             */
/*   Updated: 2026/02/17 19:17:41 by htoe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	init_exec(t_exec *exec)
{
	exec->saved_errno = 0;
	exec->status = 0;
	exec->last_pid = 0;
	exec->pid = 0;
}

static void	wait_all_child(t_exec *exec)
{
	int	wpid;
	int	status;

	status = 0;
	while ((wpid = wait(&status) > 0))
	{
		if (wpid == exec->last_pid)
			exec->status = status;
	}
}

int	pipeline_exec(t_pipeline **pl, t_env env)
{
	int		i;
	t_exec	exec;

	init_exec(&exec);
	i = -1;
	while (++i < (*pl)->cmd_counts)
	{
		exec.pid = fork();
		if (exec.pid == -1)
			return (error_perror("fork"), 1);
		if (exec.pid == 0)
		{
			exec.saved_errno = dup_and_exec(i, *pl, env);
			pipeline_destroy(pl);
			exit(error_code_from_errno(exec.saved_errno));			
		}
		if (i + 1 == (*pl)->cmd_counts)
			exec.last_pid = exec.pid;
	}
	wait_all_child(&exec);
	return (exec.status >> 8);
}
