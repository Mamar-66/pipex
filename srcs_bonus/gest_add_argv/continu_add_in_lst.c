/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   continu_add_in_lst.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 13:52:01 by omfelk            #+#    #+#             */
/*   Updated: 2024/02/01 20:55:59 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex_bonus.h"

static void	pipe_close(t_list_argv *lst_argv);

char	*continu_here_doc_switch_stdin(t_list_argv *lst_argv)
{
	char	*buff;
	char	*text_here_doc;

	pipe_close(lst_argv);
	text_here_doc = get_next_line(STDIN_FILENO);
	if (!ft_strncmp(text_here_doc, lst_argv->here_doc_end, INT_MAX))
	{
		get_next_line(-1);
		free(lst_argv->here_doc_end);
		free(text_here_doc);
		exit (1);
	}
	else
	{
		while (1)
		{
			buff = get_next_line(STDIN_FILENO);
			if (!ft_strncmp(buff, lst_argv->here_doc_end, INT_MAX))
				break ;
			text_here_doc = ft_strjoin(text_here_doc, buff);
			free(buff);
		}
	}
	get_next_line(-1);
	return (free(buff), text_here_doc);
}

static void	pipe_close(t_list_argv *lst_argv)
{
	close(lst_argv->pipe_fd[0]);
	dup2(lst_argv->pipe_fd[1], STDOUT_FILENO);
	close(lst_argv->pipe_fd[1]);
}
