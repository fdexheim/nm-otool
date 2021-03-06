/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 13:38:09 by fdexheim          #+#    #+#             */
/*   Updated: 2018/10/11 12:43:45 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/nm.h"

void		debug_env(t_env *env)
{
	putstr_ghetto("\nflag r = ");
	put_unsigned_char_ghetto_hex((unsigned char)env->flags.r);
	putstr_ghetto("\nflag p = ");
	put_unsigned_char_ghetto_hex((unsigned char)env->flags.p);
	putstr_ghetto("\nflag j = ");
	put_unsigned_char_ghetto_hex((unsigned char)env->flags.j);
	putstr_ghetto("\nflag u = ");
	put_unsigned_char_ghetto_hex((unsigned char)env->flags.u);
	putstr_ghetto("\nflag U = ");
	put_unsigned_char_ghetto_hex((unsigned char)env->flags.uppercase_u);
	putstr_ghetto("\nflag file_opened = ");
	put_unsigned_char_ghetto_hex((unsigned char)env->flags.file_opened);
	putstr_ghetto("\nflag fstat_sucess = ");
	put_unsigned_char_ghetto_hex((unsigned char)env->flags.fstat_sucess);
	putstr_ghetto("\nflag ptr_mmaped = ");
	put_unsigned_char_ghetto_hex((unsigned char)env->flags.ptr_mmaped);
	putstr_ghetto("\n");
}

void		free_env(t_env *env)
{
	if (env->flags.file_opened == true)
		close(env->fd);
	if (env->flags.ptr_mmaped == true)
		munmap(env->ptr_start, env->file_stats.st_size);
	free(env);
}

void		clean_exit(t_env *env)
{
	free_env(env);
	exit(0);
}
