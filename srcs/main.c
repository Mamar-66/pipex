/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 20:48:53 by omfelk            #+#    #+#             */
/*   Updated: 2024/02/01 20:37:01 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_list_argv	lst_argv;

	lst_argv.i_cmd = 0;
	lst_argv.fd_output = -1;
	lst_argv.cmd_with_opt = NULL;
	lst_argv.path_ok = NULL;
	lst_argv.here_doc_end = NULL;
	if (argc == 5)
	{
		if (add_in_lst(argv, argc, &lst_argv))
		{
			add_in_tab_path(envp, &lst_argv);
			lst_argv.i_cmd--;
			ex_cmd(&lst_argv);
			free_lst_argv(&lst_argv);
		}
	}
	else
		ft_printf("error nb argm = %d\n", argc);
	return (1);
}
