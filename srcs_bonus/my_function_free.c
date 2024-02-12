/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_function_free.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 21:43:29 by omfelk            #+#    #+#             */
/*   Updated: 2024/02/01 20:57:09 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	free_lst_argv(t_list_argv *lst_argv)
{
	if (lst_argv->path_ok)
		free(lst_argv->path_ok);
	if (lst_argv->here_doc_end)
		free(lst_argv->here_doc_end);
	if (lst_argv->cmd_with_opt)
		free_tab(lst_argv->cmd_with_opt);
	if (lst_argv->tab_path)
		free_tab(lst_argv->tab_path);
	free(lst_argv->tab_cmd);
	close(lst_argv->fd_input);
	close(lst_argv->fd_output);
}

void	free_tab(char **tab)
{
	int	j;

	j = 0;
	while (tab[j])
	{
		free(tab[j]);
		j++;
	}
	free(tab);
}
