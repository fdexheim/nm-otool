/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_nm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 14:26:03 by fdexheim          #+#    #+#             */
/*   Updated: 2018/10/11 12:41:20 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/nm.h"

bool			is_file(const char *argv)
{
	int			fd;

	if ((fd = open(argv, O_RDONLY)) < 0)
	{
		return (false);
	}
	else
		close(fd);
	return (true);
}

static void		parse_nm_flag(t_env *env, const char *arg)
{
	size_t		i;

	i = 0;
	while (arg[i] != '-')
		i++;
	i++;
	while (i < strlen_ghetto(arg))
	{
		env->flags.r = arg[i] == 'r' ? true : env->flags.r;
		env->flags.p = arg[i] == 'p' ? true : env->flags.p;
		env->flags.j = arg[i] == 'j' ? true : env->flags.j;
		env->flags.u = arg[i] == 'u' ? true : env->flags.u;
		env->flags.uppercase_u = arg[i] == 'U' ? true : env->flags.uppercase_u;
		i++;
	}
}

void			parse_nm_args(t_env *env)
{
	int			i;

	i = 1;
	while (i < env->argc)
	{
		if (is_file(env->argv[i]) == false)
		{
			parse_nm_flag(env, env->argv[i]);
		}
		else
			env->flags.nbfiles++;
		i++;
	}
}
