/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 15:32:50 by fdexheim          #+#    #+#             */
/*   Updated: 2018/10/11 13:34:29 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/nm.h"

static bool			reset(t_env *env, const int i)
{
	env->symtab_cmd = NULL;
	env->syms_start = NULL;
	env->flags.right_cputype_found = false;
	env->target = env->argv[i];
	open_file(env);
	if (env->flags.file_opened == true)
		fstat_file(env);
	if (env->flags.fstat_sucess == true)
		mmap_ptr(env);
	if (env->flags.ptr_mmaped == true)
	{
		env->file_size = env->file_stats.st_size;
		env->ptr = env->ptr_start;
		return (true);
	}
	return (false);
}

static int			parse_loop(t_env *env, const int i)
{
	env->path = env->argv[i];
	if (is_file(env->argv[i]))
	{
		if (reset(env, i) == false)
			return (EXIT_FAILURE);
		if (full_check_file(env) == true)
			nm_handle_magic_number(env);
		else
		{
			putstr_ghetto("[Error] : \"");
			putstr_ghetto(env->target);
			putstr_ghetto("\" appears to be either invalid or corrupted\n");
			if (env->flags.nbfiles > 1)
				write(1, "\n", 1);
			close_file(env);
			munmap_ptr(env);
			return (EXIT_FAILURE);
		}
		close_file(env);
		munmap_ptr(env);
	}
	else
		env->target = NULL;
	return (EXIT_SUCCESS);
}

int					nm(t_env *env)
{
	int		i;
	int		ret;

	ret = EXIT_SUCCESS;
	parse_nm_args(env);
	i = 1;
	while (i < env->argc)
	{
		if (parse_loop(env, i) == EXIT_FAILURE)
			ret = EXIT_FAILURE;
		i++;
	}
	return (ret);
}
