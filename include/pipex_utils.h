/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htoe <htoe@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 03:15:58 by htoe              #+#    #+#             */
/*   Updated: 2026/02/08 07:50:48 by htoe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_UTILS_H
# define PIPEX_UTILS_H

# include <unistd.h>
# include <stdlib.h>
# include "libft.h"

char	*join_path(const char *path, const char *cmd);
char	**path_list(char **envp);
char	*resolve_path(const char *cmd, char **envp);
void	free_split(char **arr);

#endif
