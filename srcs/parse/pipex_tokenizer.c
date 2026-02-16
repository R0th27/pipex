/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_tokenizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htoe <htoe@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 16:58:45 by htoe              #+#    #+#             */
/*   Updated: 2026/02/16 17:43:54 by htoe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_parse_case	count_token(char *str, t_token *token)
{
	while (str[++token->i])
	{
		if (!token->in_sq && str[token->i] == ' ')
			token->in_word = 0;
		else
		{
			if (!token->in_word && ++token->count)
				token->in_word = 1;
			if (str[token->i] == '\'')
				token->in_sq = !token->in_sq;
			else if (str[token->i] == '\\' && !token->in_sq)
			{
				if (!str[token->i + 1])
					return (PARSE_BACKSLASH);
				token->i++;
			}
		}
	}
	if (token->in_sq)
		return (PARSE_UNCLOSED_QUOTE);
	return (PARSE_OK);
}

int	token_counter(char *str, t_parse_case *state)
{
	t_token			token;

	token.in_sq = 0;
	token.in_word = 0;
	token.count = 0;
	token.i = -1;
	*state = count_token(str, &token);
	if (*state != PARSE_OK)
		return (0);
	return (token.count);
}

char	**cmd_tokenizer(char *cmd_str)
{
	char			**argv;
	int				token_count;
	t_parse_case	state;

	token_count = token_counter(cmd_str, &state);
	printf("token count: %d\n", token_count);
	argv = NULL;
	return (argv);
}
