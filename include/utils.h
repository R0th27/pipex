/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htoe <htoe@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 03:15:58 by htoe              #+#    #+#             */
/*   Updated: 2026/02/08 04:27:52 by htoe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <unistd.h>
# include <stdlib.h>
# include "libft.h"
# include <stdio.h>

char	*join_path(const char *path, const char *cmd);
char	**path_list(char **envp);
char	*resolve_path(const char *cmd, char **envp);
void	free_split(char **arr);

#endif
