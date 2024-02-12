/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_path_caract.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 11:38:59 by omfelk            #+#    #+#             */
/*   Updated: 2024/02/01 12:52:28 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

char	**text_with_caract_spe(char *text)
{
	char	**tab;
	int		start;
	int		j;

	j = 0;
	start = 0;
	if (text[start])
	{
		tab = ft_calloc(sizeof(char *), 2);
		tab[j] = retunr_word(text, '\'', &start);
		j++;
		while (text[start])
		{
			tab = ft_realloc_tab(tab, 2);
			tab[j] = retunr_word(text, '\'', &start);
			j++;
		}
	}
	return (tab);
}

char	*retunr_word(char *text, char delim, int *start)
{
	char	*text_return;
	int		i;

	i = *start;
	while (text[i] == ' ' && text[i])
		i++;
	if (text[i] == delim)
	{
		text_return = return_cmd(text, '\'', &i);
		*start = i;
		return (text_return);
	}
	else
	{
		text_return = return_word_simple_delim(text, &i, delim);
		*start = i;
	}
	return (text_return);
}

char	*return_word_simple_delim(char *text, int *start, char delim)
{
	char	*text_return;
	int		i;
	int		k;

	i = *start;
	k = 0;
	while (text[i] != ' ' && text[i])
	{
		i++;
		k++;
	}
	text_return = ft_calloc(sizeof(char *), k + 1);
	if (!text_return)
		return (NULL);
	i = i - k;
	k = 0;
	while (text[i] != ' ' && text[i] && text[i] != delim)
	{
		text_return[k] = text[i];
		k++;
		i++;
	}
	text_return[k] = '\0';
	*start = i;
	return (text_return);
}

char	*return_cmd(char *text, char delim, int *start)
{
	char	*text_return;
	int		i;
	int		j;
	int		k;

	i = *start;
	k = 0;
	i++;
	j = i;
	while (text[j] && text[j++] != delim)
		k++;
	text_return = ft_calloc(sizeof(char *), k + 1);
	if (!text_return)
		return (NULL);
	k = 0;
	while (text[i] && text[i] != delim)
	{
		text_return[k] = text[i];
		i++;
		k++;
	}
	*start = ++i;
	return (text_return);
}
