/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htoe <htoe@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 13:44:50 by htoe              #+#    #+#             */
/*   Updated: 2026/02/18 13:03:38 by htoe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	env_init(int argc, char **argv, char **envp, t_env *env)
{
	env->argc = argc;
	env->argv = argv;
	env->envp = envp;
}

void	setup_io(t_env env, t_pipeline *pl)
{
	int	start;

	start = 1 + (pl->io_type == INPUT_HEREDOC);
	pl->infile = setup_input_fd(pl->io_type, env.argv[start]);
	if (pl->infile < 0)
	{
		if (pl->io_type == INPUT_HEREDOC)
			error_perror("heredoc");
		else
			error_perror(env.argv[1]);
		pl->infile = open("/dev/null", O_RDONLY);
		if (pl->infile < 0)
			pl->infile = STDIN_FILENO;
	}
	pl->outfile = setup_output_fd(pl->io_type, env.argv[env.argc - 1]);
	if (pl->outfile < 0)
		error_perror(env.argv[env.argc - 1]);
}

int	pipeline_init(t_env env, t_pipeline **pl)
{
	*pl = (t_pipeline *)malloc(sizeof(t_pipeline));
	if (!(*pl))
		return (0);
	(*pl)->io_type = detect_input_type(env.argv[1]);
	(*pl)->cmd_counts = env.argc - 3 - ((*pl)->io_type == INPUT_HEREDOC);
	(*pl)->cmds = ft_calloc((*pl)->cmd_counts, sizeof(t_cmd));
	if (!(*pl)->cmds)
		return (free(*pl), 0);
	(*pl)->infile = -1;
	(*pl)->outfile = -1;
	(*pl)->envp = env.envp;
	setup_io(env, *pl);
	return (1);
}

int	pipeline_fill(t_env env, t_pipeline *pl)
{
	int		i;
	int		start;
	char	**dirs;
	t_error	err;

	err = ERR_OK;
	dirs = extract_path_dirs(env.envp);
	start = 2 + (pl->io_type == INPUT_HEREDOC);
	i = 0;
	while (i < pl->cmd_counts)
	{
		pl->cmds[i].argv = cmd_tokenizer(env.argv[start], &err);
		if (err != ERR_OK)
			return (free_array(&dirs), error_perror("malloc"), 0);
		if (pl->cmds[i].argv)
			pl->cmds[i].paths = build_paths(pl->cmds[i].argv[0], dirs, &err);
		if (err != ERR_OK)
			return (free_array(&dirs), error_perror("malloc"), 0);
		i++;
		start++;
	}
	return (free_array(&dirs), 1);
}
