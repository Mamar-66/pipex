/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:23:23 by omfelk            #+#    #+#             */
/*   Updated: 2024/02/01 20:56:07 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex_bonus.h"

bool	ex_cmd(t_list_argv *lst_argv)
{
	while (lst_argv->tab_cmd[++lst_argv->i_cmd])
	{
		if (!return_path(lst_argv))
			return (false);
		ft_ex_execve(lst_argv);
	}
	if (lst_argv->here_doc_end)
		lst_argv->fd_output = open(lst_argv->file_output, O_CREAT
				| O_RDWR | O_APPEND, 0644);
	else
		lst_argv->fd_output = open(lst_argv->file_output, O_CREAT
				| O_RDWR | O_TRUNC, 0644);
	if (lst_argv->fd_output == -1)
	{
		perror("file_output ");
		return (false);
	}
	suite_ex_cmd(lst_argv);
	return (true);
}

void	suite_ex_cmd(t_list_argv *lst_argv)
{
	char	*text_file_output;

	dup2(lst_argv->fd_output, STDOUT_FILENO);
	text_file_output = get_next_line(STDIN_FILENO);
	while (text_file_output)
	{
		ft_printf("%s", text_file_output);
		free(text_file_output);
		text_file_output = get_next_line(STDIN_FILENO);
	}
}

bool	ft_ex_execve(t_list_argv *lst_argv)
{
	pid_t	child_pid;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		perror("error pipe ");
	child_pid = fork();
	if (child_pid == -1)
	{
		perror("error child_pid ");
		return (false);
	}
	else if (child_pid == 0)
		ex_child(lst_argv, pipe_fd);
	else
		ex_father(lst_argv, pipe_fd, child_pid);
	return (true);
}

bool	ex_child(t_list_argv *lst_argv, int	*pipe_fd)
{
	close(pipe_fd[0]);
	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
	{
		perror("error <dup2(pipe_fd[1], STDOUT_FILENO)> ");
		return (false);
	}
	close(pipe_fd[1]);
	if (execve(lst_argv->path_ok, lst_argv->cmd_with_opt, NULL) == -1)
	{
		perror("error execve ");
		return (false);
	}
	return (true);
}

bool	ex_father(t_list_argv *lst_argv, int *pipe_fd, int child_pid)
{
	(void)lst_argv;
	close(pipe_fd[1]);
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
	{
		perror("(dup2(pipe_fd[0], STDIN_FILENO) ");
		return (false);
	}
	close(pipe_fd[0]);
	waitpid(child_pid, NULL, 0);
	return (true);
}
