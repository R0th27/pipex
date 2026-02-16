/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_tokenizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htoe <htoe@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 11:20:49 by htoe              #+#    #+#             */
/*   Updated: 2026/02/16 13:18:13 by htoe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	count_token(char *s, t_parse_case *state)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		count++;
		if (s[i] == '\'')
			single_quotes_skip(s, &i, state);
		else if (s[i] == ' ')
		{
			space_skip(s, &i, state);
			count--;
		}
		else
			normal_skip(s, &i, state);
		if (*state != PARSE_OK)
			return (0);
		if (s[i])
			i++;
	}
	return (*state = PARSE_OK, count);
}

char	**tokenizer(char *cmd_str)
{
	char			**tokens;
	int				token_count;
	t_parse_case	state;

	state = PARSE_OK;
	token_count = count_token(cmd_str, &state);
	printf("token count: %d\n", token_count);
	(void)state;
	tokens = NULL;
	return (tokens);
}
