/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 09:01:32 by fdexheim          #+#    #+#             */
/*   Updated: 2018/10/11 12:38:31 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/nm.h"

static t_obj_ctrl	mecho_alone(t_env *env, int mnum)
{
	t_obj_ctrl		ctrl;

	ctrl.obj_size = env->file_stats.st_size;
	ctrl.obj_offset = 0;
	ctrl.m_num = mnum;
	ctrl.obj_hdr = env->ptr_start;
	return (ctrl);
}

static t_obj_ctrl	fet_alone(t_env *env, int mnum)
{
	t_obj_ctrl		ctrl;

	ctrl.obj_size = env->file_stats.st_size;
	ctrl.obj_offset = 0;
	ctrl.m_num = mnum;
	ctrl.obj_hdr = env->ptr_start;
	return (ctrl);
}

static t_obj_ctrl	er_alone(t_env *env)
{
	t_obj_ctrl		ctrl;

	ctrl.obj_size = env->file_stats.st_size;
	ctrl.obj_hdr = env->ptr_start;
	ctrl.obj_offset = 0;
	ctrl.m_num = 0;
	return (ctrl);
}

static void			special_macho_multiple_files(t_env *env, uint32_t magic)
{
	if ((magic == MH_MAGIC_64 || magic == MH_MAGIC || magic == MH_CIGAM_64
			|| magic == MH_CIGAM) && env->flags.nbfiles > 1)
	{
		putstr_ghetto("\n");
		putstr_ghetto(env->path);
		putstr_ghetto(":\n");
	}
}

void				nm_handle_magic_number(t_env *env)
{
	uint32_t		magic;

	magic = *(uint32_t*)env->ptr_start;
	special_macho_multiple_files(env, magic);
	if (magic == MH_MAGIC_64 || magic == MH_CIGAM_64)
	{
		nm_handle_macho_64(env, mecho_alone(env, magic));
		display(env, mecho_alone(env, magic));
	}
	else if (magic == MH_MAGIC || magic == MH_CIGAM)
	{
		nm_handle_macho_32(env, mecho_alone(env, magic));
		display(env, mecho_alone(env, magic));
	}
	else if (magic == FAT_MAGIC || magic == FAT_CIGAM)
		nm_handle_fat_32(env, fet_alone(env, magic));
	else if (magic == FAT_MAGIC_64
			|| magic == FAT_CIGAM_64)
		nm_handle_fat_64(env, fet_alone(env, magic));
	else if (!strncmp_ghetto(env->ptr_start, "!<arch>\n", 8))
		nm_handle_ar(env, er_alone(env));
	else
		putstr_ghetto("[Warning] : unknown magic number encountered\n");
}
