/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htoe <htoe@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 18:30:01 by htoe              #+#    #+#             */
/*   Updated: 2026/02/17 14:08:11 by htoe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_in_type	detect_input_type(const char *arg)
{
	if (!ft_strncmp(arg, "here_doc", 9))
		return (INPUT_HEREDOC);
	return (INPUT_FILE);
}
