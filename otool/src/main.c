/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 08:41:24 by fdexheim          #+#    #+#             */
/*   Updated: 2018/10/11 14:30:47 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/otool.h"

static void		help(void)
{
	putstr_ghetto("./otool -[flags] [file]\n");
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
	ret->flags.file_opened = false;
	ret->flags.fstat_sucess = false;
	ret->flags.ptr_mmaped = false;
	ret->flags.rightcputype_found = false;
	ret->flags.rightcpusubtype_found = false;
	return (ret);
}

int				main(int argc, char **argv)
{
	t_env		*env;
	int			ret;

	if (argc < 2)
	{
		help();
		return (0);
	}
	env = setup_env(argc, argv);
	if (env != NULL)
	{
		ret = otool(env);
		free_env(env);
		return (ret);
	}
	return (0);
}
