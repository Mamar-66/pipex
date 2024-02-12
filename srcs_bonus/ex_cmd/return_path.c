/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 20:09:40 by omfelk            #+#    #+#             */
/*   Updated: 2024/02/01 20:56:21 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex_bonus.h"

bool	return_path(t_list_argv *lst_argv)
{
	cmd_with_option(lst_argv);
	if (lst_argv->path_ok)
		free(lst_argv->path_ok);
	lst_argv->path_ok = checked_access(lst_argv->tab_path,
			lst_argv->cmd_with_opt[0]);
	if (!lst_argv->path_ok)
	{
		perror("error cmd ");
		return (false);
	}
	free(lst_argv->cmd_with_opt[0]);
	lst_argv->cmd_with_opt[0] = ft_strdup(lst_argv->path_ok);
	return (true);
}

char	*checked_access(char **tab_path, char *cmd)
{
	char	*path_cmd;
	int		j;

	j = 0;
	if (!cmd)
		return (NULL);
	while (tab_path[j])
	{
		path_cmd = ft_strdup(tab_path[j]);
		path_cmd = ft_realloc(path_cmd, ft_strlen(cmd) + 1);
		ft_strlcat(path_cmd, "/",
			ft_strlen(tab_path[j]) + ft_strlen(cmd) + 1);
		ft_strlcat(path_cmd, cmd,
			ft_strlen(tab_path[j]) + ft_strlen(cmd) * 3);
		if (access(path_cmd, X_OK | R_OK) == 0)
			break ;
		free(path_cmd);
		j++;
	}
	if (tab_path[j])
		return (path_cmd);
	else
		return (NULL);
}

void	cmd_with_option(t_list_argv *lst_argv)
{
	if (lst_argv->cmd_with_opt)
		free_tab(lst_argv->cmd_with_opt);
	if (chrch_caract(lst_argv->tab_cmd[lst_argv->i_cmd], '\'') > 0)
		lst_argv->cmd_with_opt = text_with_caract_spe(
				lst_argv->tab_cmd[lst_argv->i_cmd]);
	else
		lst_argv->cmd_with_opt = ft_split(
				lst_argv->tab_cmd[lst_argv->i_cmd], ' ');
	if (!lst_argv->cmd_with_opt)
	{
		perror("error ft_split for lst_argv->cmd_with_opt ");
		return ;
	}
}

int	chrch_caract(char *text, char c)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while (text[i])
	{
		if (text[i] == c)
			nb++;
		i++;
	}
	if (nb != 0 && nb % 2 != 0)
		return (-1);
	return (nb / 2);
}
