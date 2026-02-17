/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_paths.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htoe <htoe@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 17:29:19 by htoe              #+#    #+#             */
/*   Updated: 2026/02/17 18:31:37 by htoe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**extract_path_dirs(char **envp)
{
	int	i;

	if (!envp || !*envp)
		return (NULL);
	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (!envp[i])
		return (NULL);
	return (ft_split(envp[i] + 5, ':'));
}

static char	*join_path_cmd(const char *path, const char *cmd)
{
	char	*path_slash;
	char	*path_full;

	path_slash = ft_strjoin(path, "/");
	if (!path_slash)
		return (NULL);
	path_full = ft_strjoin(path_slash, cmd);
	free(path_slash);
	return (path_full);
}

static char	**build_candidates(char *cmd, char **dirs, t_error *err)
{
	char	**candidates;
	int		i;

	i = 0;
	while (dirs[i])
		i++;
	candidates = (char **)malloc(sizeof(char *) * (i + 1));
	if (!candidates)
		return (*err = ERR_MALLOC, NULL);
	i = -1;
	while (dirs[++i])
	{
		candidates[i] = join_path_cmd(dirs[i], cmd);
		if (!candidates[i])
			return (free_array(&candidates), *err = ERR_MALLOC, NULL);
	}
	candidates[i] = NULL;
	return (*err = ERR_OK, candidates);
}

char	**build_paths(char *cmd, char **dirs, t_error *err)
{
	char	**paths;

	if (!cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		paths = (char **)malloc(sizeof(char *) * 2);
		if (!paths)
			return (*err = ERR_MALLOC, NULL);
		paths[0] = ft_strdup(cmd);
		paths[1] = NULL;
		return (*err = ERR_OK, paths);
	}
	if (!dirs || !*dirs)
		return (NULL);
	paths = build_candidates(cmd, dirs, err);
	if (*err != ERR_OK)
		return (*err = ERR_MALLOC, NULL);
	return (*err = ERR_OK, paths);
}
