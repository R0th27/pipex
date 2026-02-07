/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htoe <htoe@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 04:37:49 by htoe              #+#    #+#             */
/*   Updated: 2026/02/08 05:28:30 by htoe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H
# define CMD_H

# include <unistd.h>
# include <stdlib.h>
# include "libft.h"
# include "utils.h"
# include "error.h"

typedef struct s_cmd
{
	char	**argv;
	char	*path;
	int		in_fd;
	int		out_fd;
}	t_cmd;

t_cmd	*cmd_create(char *cmd_str, char **envp);
void	cmd_destroy(t_cmd *cmd);
void	exec_cmd(t_cmd *cmd, char **envp);

#endif
