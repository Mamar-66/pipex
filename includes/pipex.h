/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 20:49:52 by omfelk            #+#    #+#             */
/*   Updated: 2024/02/01 20:50:40 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../srcs_bonus/get_next_line/get_next_line.h"
# include "printf/include/ft_printf.h"
# include "libft/libft.h"
# include <unistd.h>
# include <stdbool.h>
# include <fcntl.h>
# include <sys/wait.h>

typedef struct s_list_info_argv
{
	char	*file_input;
	int		fd_input;
	char	*file_output;
	int		fd_output;
	char	*here_doc_end;
	int		pipe_fd[2];
	char	**tab_path;
	char	*path_ok;
	char	**cmd_with_opt;
	char	**tab_cmd;
	int		i_cmd;
}	t_list_argv;

// my_function_free.c
void	free_lst_argv(t_list_argv *lst_argv);
void	free_tab(char **tab);
/////////////////////
/* gest_add_argv */
// add_in_lst.c
bool	add_in_lst(char **argv, int argc, t_list_argv *lst_argv);
void	add_in_tab_path(char **envp, t_list_argv *lst_argv);
bool	if_here_doc(char **argv, int argc, t_list_argv *lst_argv);
///////////
// continu_add_in_lst.c
char	*continu_here_doc_switch_stdin(t_list_argv *lst_argv);
///////////////////////
/* ------------- */
/* ex_cmd */
bool	ex_cmd(t_list_argv *lst_argv);
void	suite_ex_cmd(t_list_argv *lst_argv);
bool	ft_ex_execve(t_list_argv *lst_argv);
bool	ex_child(t_list_argv *lst_argv, int	*pipe_fd);
bool	ex_father(t_list_argv *lst_argv, int *pipe_fd, int child_pid);
/* ----- */
/*  */
/* ------ */
/* return_path */
bool	return_path(t_list_argv *lst_argv);
char	*checked_access(char **tab_path, char *cmd);
void	cmd_with_option(t_list_argv *lst_argv);
int		chrch_caract(char *text, char c);
/* ----------- */
/* return_path_caract.c */
char	**text_with_caract_spe(char *text);
char	*return_cmd(char *text, char delim, int *start);
char	*retunr_word(char *text, char delim, int *start);
char	*return_word_simple_delim(char *text, int *start, char delim);
/*----------------------*/
#endif