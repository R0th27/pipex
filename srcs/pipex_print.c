/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htoe <htoe@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 17:47:09 by htoe              #+#    #+#             */
/*   Updated: 2026/02/17 17:56:04 by htoe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	cmd_display(t_cmd cmd)
{
	int	i;

	printf("[argv] : ");
	if (cmd.argv)
	{
		i = -1;
		while (cmd.argv[++i])
			printf("[%s]", cmd.argv[i]);
	}
	else
		printf("<NIL>");
	printf("\n");
	printf("[paths]\n");
	if (cmd.paths)
	{
		i = -1;
		while (cmd.paths[++i])
			printf("[%s]", cmd.paths[i]);
	}
	else
		printf("<NIL>");
	printf("\n");
}

void	pipeline_display(t_pipeline *pl)
{
	int	i;

	printf("##### PIPELINE #####\n");
	printf("### cmd_counts: %d\n", pl->cmd_counts);
	printf("### iotypes: %d\n", pl->io_type);
	printf("### infile: %d\n", pl->infile);
	printf("### outfile: %d\n", pl->outfile);
	printf("##### PIPELINE #####\n\n");
	i = 0;
	while (i < pl->cmd_counts)
	{
		printf("##### CMD [%d] #####\n", i);
		cmd_display(pl->cmds[i]);
		printf("##### CMD [%d] #####\n\n", i);
		i++;
	}
}
