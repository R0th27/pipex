/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_skip.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htoe <htoe@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 13:15:08 by htoe              #+#    #+#             */
/*   Updated: 2026/02/16 15:58:48 by htoe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	count_token(char *s, t_parse_case *state)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	if (s[i] && !s[i + 1])
		return (1);
	while (s[i])
	{
		count++;
		if (s[i] == '\'')
			*state = single_quotes_skip(s, &i);
		else if (s[i] == ' ')
		{
			space_skip(s, &i);
			count--;
		}
		else
			*state = normal_skip(s, &i);
		if (*state != PARSE_OK)
			return (0);
		if (s[i])
			i++;
	}
	return (*state = PARSE_OK, count);
}

void	space_skip(char *s, int *index)
{
	while (s[*index] && s[*index] == ' ')
		(*index)++;
	(*index)--;
}

t_parse_case	single_quotes_skip(char *s, int *index)
{
	int	quote_count;

	quote_count = 1;
	while (s[*index])
	{
		(*index)++;
		if (s[*index] == '\'')
			quote_count++;
		if (s[*index] == '\'' && (!s[*index + 1] || s[*index + 1] == ' '))
			break ;
	}
	if (quote_count % 2 == 0)
		return (PARSE_OK);
	else
		return (PARSE_UNCLOSED_QUOTE);
}

t_parse_case	backslash_skip(char *s, int *index)
{
	if (!s[*index + 1])
		return (PARSE_BACKSLASH);
	(*index)++;
	return (PARSE_OK);
}

t_parse_case	normal_skip(char *s, int *index)
{
	t_parse_case	state;

	state = PARSE_OK;
	while (s[*index])
	{
		if (s[*index] == '\'')
			state = single_quotes_skip(s, index);
		else if (s[*index] == '\\')
			state = backslash_skip(s, index);
		else if (!s[*index] || s[*index] == ' ')
			break ;
		if (state != PARSE_OK)
			return (state);
		(*index)++;
	}
	return (PARSE_OK);
}
