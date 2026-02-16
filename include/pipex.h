/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htoe <htoe@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 21:57:33 by htoe              #+#    #+#             */
/*   Updated: 2026/02/16 13:16:10 by htoe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include "pipex_types.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <fcntl.h>
# include <stdbool.h>
# include <sys/types.h>
# include <sys/wait.h>

//parse
char	**tokenizer(char *cmd_str);

//skip
void	space_skip(char *s, int *index, t_parse_case *state);
void	single_quotes_skip(char *s, int *index, t_parse_case *state);
void	backslash_skip(char *s, int *index, t_parse_case *state);
void	normal_skip(char *s, int *index, t_parse_case *state);

#endif
