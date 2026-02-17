/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_freeup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htoe <htoe@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 18:24:41 by htoe              #+#    #+#             */
/*   Updated: 2026/02/17 14:00:08 by htoe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

void	cmd_destroy(t_cmd *cmd)
{
	if (!cmd)
		return ;
	free_array(&(cmd->argv));
	free_array(&(cmd->paths));
}

void	pipeline_destroy(t_pipeline **pl)
{
	int	i;

	if (!(*pl))
		return ;
	if ((*pl)->infile >= 0)
		close((*pl)->infile);
	if ((*pl)->outfile >= 0)
		close((*pl)->outfile);
	i = 0;
	while (i < (*pl)->cmd_counts)
	{
		cmd_destroy(&((*pl)->cmds[i]));
		i++;
	}
	free((*pl)->cmds);
	free((*pl));
	(*pl) = NULL;
}
