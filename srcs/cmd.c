/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htoe <htoe@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 04:40:15 by htoe              #+#    #+#             */
/*   Updated: 2026/02/08 05:02:22 by htoe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

t_cmd	*cmd_create(char *cmd_str, char **envp)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd -> cmd_argv = ft_split(cmd_str, ' ');
	if (!cmd -> cmd_argv || !cmd -> cmd_argv[0])
		return (cmd_destroy(cmd), NULL);
	cmd -> path = resolve_path(cmd -> cmd_argv[0], envp);
	cmd -> in_fd = -1;
	cmd -> out_fd = -1;
	return (cmd);
}

void	cmd_destroy(t_cmd *cmd)
{
	if (!cmd)
		return ;
	free_split(cmd -> cmd_argv);
	free(cmd -> path);
	free(cmd);
}

void	exec_cmd(t_cmd *cmd, char **envp);