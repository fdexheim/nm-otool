/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 09:01:32 by fdexheim          #+#    #+#             */
/*   Updated: 2018/10/04 15:58:23 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/otool.h"

static t_obj_ctrl	mecho_alone(t_env *env, int mnum)
{
	t_obj_ctrl		ctrl;

	ctrl.obj_size = env->file_stats.st_size;
	ctrl.obj_offset = 0;
	ctrl.m_num = mnum;
	ctrl.obj_hdr = env->ptr_start;
	putstr_ghetto(env->path);
	write(1, ":\n", 2);
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

static t_obj_ctrl	static_leb_alone(t_env *env, int mnum)
{
	t_obj_ctrl		ctrl;

	ctrl.obj_size = env->file_stats.st_size;
	ctrl.obj_offset = 0;
	ctrl.m_num = mnum;
	ctrl.obj_hdr = env->ptr_start;
	return (ctrl);
}

void				otool_handle_magic_number(t_env *env)
{
	uint32_t		magic;

	magic = *(uint32_t*)env->ptr_start;
	if (magic == MH_MAGIC_64 || magic == MH_CIGAM_64)
		otool_handle_macho_64(mecho_alone(env, magic));
	else if (magic == MH_MAGIC || magic == MH_CIGAM)
		otool_handle_macho_32(mecho_alone(env, magic));
	else if (magic == FAT_MAGIC || magic == FAT_CIGAM)
		otool_handle_fat_32(env, fet_alone(env, magic));
	else if (magic == FAT_MAGIC_64
			|| magic == FAT_CIGAM_64)
		otool_handle_fat_64(env, fet_alone(env, magic));
	else if (!strncmp_ghetto(env->ptr_start, "!<arch>\n", 8))
		otool_handle_ar(env, static_leb_alone(env, magic));
	else
		putstr_ghetto("UKNOWN MAGIC SOMETHING'S FUCKT UP MATE\n");
}
