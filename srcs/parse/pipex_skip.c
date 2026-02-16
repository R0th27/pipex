/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_skip.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htoe <htoe@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 13:15:08 by htoe              #+#    #+#             */
/*   Updated: 2026/02/16 13:18:01 by htoe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	space_skip(char *s, int *index, t_parse_case *state)
{
	while (s[*index] && s[*index] == ' ')
		(*index)++;
	(*index)--;
	*state = PARSE_OK;
}

void	single_quotes_skip(char *s, int *index, t_parse_case *state)
{
	int	quote_count;

	quote_count = 1;
	while (s[*index])
	{
		(*index)++;
		if (s[*index] == '\'')
			quote_count++;
		if (s[*index] == '\'' && (s[*index + 1] == ' ' || !s[*index + 1]))
			break ;
	}
	if (quote_count % 2 == 0)
		*state = PARSE_OK;
	else
		*state = PARSE_UNCLOSED_QUOTE;
}

void	backslash_skip(char *s, int *index, t_parse_case *state)
{
	if (!s[*index + 1])
	{
		*state = PARSE_BACKSLASH;
		return ;
	}
	*state = PARSE_OK;
	(*index)++;
}

void	normal_skip(char *s, int *index, t_parse_case *state)
{
	while (s[*index])
	{
		if (s[*index] == '\'')
			single_quotes_skip(s, index, state);
		else if (s[*index] == '\\')
			backslash_skip(s, index, state);
		else if (!s[*index] || s[*index] == ' ')
			break ;
		if (*state != PARSE_OK)
			return ;
		(*index)++;
	}
	*state = PARSE_OK;
}
