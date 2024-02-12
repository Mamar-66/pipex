/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_in_lst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 19:55:51 by omfelk            #+#    #+#             */
/*   Updated: 2024/01/16 16:00:54 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex_bonus.h"

bool	add_in_lst(char **argv, int argc, t_list_argv *lst_argv)
{
	int		j;

	j = 0;
	if (!if_here_doc(argv, argc, lst_argv))
		return (false);
	lst_argv->tab_cmd = ft_calloc(sizeof(char *), (argc - 2));
	if (!lst_argv->tab_cmd)
	{
		perror("error lst_argv->tab_cmd ");
		return (NULL);
	}
	while (j < (argc - 3))
	{
		lst_argv->tab_cmd[j] = argv[(j + 2)];
		j++;
	}
	return (true);
}

void	add_in_tab_path(char **envp, t_list_argv *lst_argv)
{
	int	j;

	j = 0;
	while (envp[j])
	{
		if (ft_strncmp(envp[j], "PATH=", 4) == 0)
			break ;
		j++;
	}
	lst_argv->tab_path = ft_split(envp[j] + 5, ':');
}

bool	if_here_doc(char **argv, int argc, t_list_argv *lst_argv)
{
	lst_argv->file_input = argv[1];
	lst_argv->fd_input = -1;
	if (!ft_strncmp(lst_argv->file_input, "here_doc", INT_MAX))
	{
		if (!add_here_doc(lst_argv, argv))
			return (false);
	}
	else
	{
		lst_argv->fd_input = open(lst_argv->file_input, O_RDONLY);
		if (lst_argv->fd_input == -1)
			perror("file_input ");
		dup2(lst_argv->fd_input, STDIN_FILENO);
	}
	lst_argv->file_output = argv[argc - 1];
	if ((lst_argv->fd_input == -1
			&& ft_strncmp(argv[1], "here_doc", INT_MAX)))
		return (false);
	return (true);
}

bool	add_here_doc(t_list_argv *lst_argv, char **argv)
{
	lst_argv->here_doc_end = ft_strdup(argv[2]);
	lst_argv->i_cmd = 1;
	lst_argv->here_doc_end = ft_realloc(lst_argv->here_doc_end,
			ft_strlen(lst_argv->here_doc_end) + 1);
	lst_argv->here_doc_end[ft_strlen(lst_argv->here_doc_end)] = '\n';
	pipe(lst_argv->pipe_fd);
	if (!here_doc_switch_stdin(lst_argv))
		return (false);
	return (true);
}

bool	here_doc_switch_stdin(t_list_argv *lst_argv)
{
	pid_t	child;
	char	*text_here_doc;

	child = fork();
	if (child == 0)
	{
		text_here_doc = continu_here_doc_switch_stdin(lst_argv);
		ft_printf("%s", text_here_doc);
		free(lst_argv->here_doc_end);
		free(text_here_doc);
		exit (true);
	}
	else
	{
		close(lst_argv->pipe_fd[1]);
		dup2(lst_argv->pipe_fd[0], STDIN_FILENO);
		close(lst_argv->pipe_fd[0]);
		waitpid(child, NULL, 0);
	}
	return (true);
}
