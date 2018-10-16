/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 12:42:29 by fdexheim          #+#    #+#             */
/*   Updated: 2018/10/11 12:43:28 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/nm.h"

static void		help(void)
{
	putstr_ghetto("./nm -flags file\n");
	putstr_ghetto("-r : displays list in reverse order\n");
}

static t_env	*setup_env(int argc, char **argv)
{
	t_env		*ret;

	if ((ret = (t_env*)malloc(sizeof(t_env))) == NULL)
	{
		putstr_ghetto("[Error] : memory allocation went wrong during booting");
		return (NULL);
	}
	ret->argc = argc;
	ret->argv = argv;
	ret->fd = -1;
	ret->target = NULL;
	ret->flags.r = false;
	ret->flags.p = false;
	ret->flags.j = false;
	ret->flags.u = false;
	ret->flags.uppercase_u = false;
	ret->symbol_list = NULL;
	ret->flags.file_opened = false;
	ret->flags.fstat_sucess = false;
	ret->flags.ptr_mmaped = false;
	ret->flags.right_cputype_found = false;
	ret->flags.nbfiles = 0;
	return (ret);
}

int				main(int argc, char **argv)
{
	t_env		*env;

	if (argc < 2)
	{
		help();
		return (EXIT_FAILURE);
	}
	env = setup_env(argc, argv);
	if (env != NULL)
	{
		return (nm(env));
		free_env(env);
	}
	return (EXIT_FAILURE);
}
