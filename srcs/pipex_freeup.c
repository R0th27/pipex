/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_freeup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htoe <htoe@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 18:24:41 by htoe              #+#    #+#             */
/*   Updated: 2026/02/16 19:01:42 by htoe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	cmd_destroy(t_cmd **cmd)
{
	if (!*cmd)
		return ;
	free_split((*cmd)->argv);
	free_split((*cmd)->paths);
	free(*cmd);
	*cmd = NULL;
}

void	free_array(char ***arr)
{
	int	i;

	if (!*arr)
		return ;
	i = 0;
	while ((*arr)[i])
		free((*arr)[i++]);
	free(*arr);
	*arr = NULL;
}
