/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 15:06:23 by fdexheim          #+#    #+#             */
/*   Updated: 2018/10/05 09:29:23 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/nm.h"

static t_obj_ctrl	fat_alone(t_env *env, const int mnum)
{
	t_obj_ctrl		ctrl;

	ctrl.obj_size = env->file_stats.st_size;
	ctrl.obj_hdr = env->ptr_start;
	ctrl.obj_offset = 0;
	ctrl.m_num = mnum;
	return (ctrl);
}

static t_obj_ctrl	macho_alone(t_env *env, const int mnum)
{
	t_obj_ctrl		ctrl;

	ctrl.obj_size = env->file_stats.st_size;
	ctrl.obj_hdr = env->ptr_start;
	ctrl.obj_offset = 0;
	ctrl.m_num = mnum;
	return (ctrl);
}

static t_obj_ctrl	ar_alone(t_env *env)
{
	t_obj_ctrl		ctrl;

	ctrl.obj_size = env->file_stats.st_size;
	ctrl.obj_hdr = env->ptr_start;
	ctrl.obj_offset = 0;
	ctrl.m_num = 0;
	return (ctrl);
}

static bool			full_check_file2(t_env *env, t_obj_ctrl ctrl)
{
	if (ctrl.m_num == MH_MAGIC_64 || ctrl.m_num == MH_CIGAM_64)
	{
		ctrl = macho_alone(env, ctrl.m_num);
		return (check_macho_64(env, ctrl));
	}
	else if (ctrl.m_num == MH_MAGIC || ctrl.m_num == MH_CIGAM)
	{
		ctrl = macho_alone(env, ctrl.m_num);
		return (check_macho_32(env, ctrl));
	}
	else if (ctrl.m_num == FAT_MAGIC || ctrl.m_num == FAT_CIGAM
			|| ctrl.m_num == FAT_MAGIC_64 || ctrl.m_num == FAT_CIGAM_64)
	{
		ctrl = fat_alone(env, ctrl.m_num);
		if (ctrl.m_num == FAT_MAGIC || ctrl.m_num == FAT_CIGAM)
			return (check_fat_32(env, ctrl));
		return (check_fat_64(env, ctrl));
	}
	else if (!strncmp_ghetto(env->ptr_start, "!<arch>\n", 8))
	{
		ctrl = ar_alone(env);
		return (check_ar(env, ctrl));
	}
	return (false);
}

bool				full_check_file(t_env *env)
{
	t_obj_ctrl		ctrl;

	if (env->file_size < 4)
		return (false);
	ctrl.m_num = *(uint32_t*)env->ptr_start;
	return (full_check_file2(env, ctrl));
}
