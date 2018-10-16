/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_arch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/26 13:46:29 by fdexheim          #+#    #+#             */
/*   Updated: 2018/10/04 16:03:45 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/otool.h"

static void					write_fat_arch(t_env *env, t_obj_ctrl fat_ctrl,
		cpu_type_t cpt)
{
	putstr_ghetto(env->path);
	write(1, " (for architecture ", 19);
	if (pui32(cpt, fat_ctrl.m_num) == CPU_TYPE_POWERPC)
		write(1, "ppc", 3);
	else if (pui32(cpt, fat_ctrl.m_num) == CPU_TYPE_I386)
		write(1, "i386", 4);
	else if (pui32(cpt, fat_ctrl.m_num) == CPU_TYPE_X86_64)
		write(1, "x86_64", 6);
	else
		write(1, "unknown", 7);
	write(1, "):\n", 3);
}

static void					write_fat_path(t_env *env)
{
	putstr_ghetto(env->path);
	write(1, ":\n", 2);
}

static void					handle_fat_bis(t_env *env, size_t obj_size)
{
	t_obj_ctrl				macho_ctrl;

	macho_ctrl.m_num = *(uint32_t *)env->ptr;
	macho_ctrl.obj_hdr = env->ptr;
	macho_ctrl.obj_size = obj_size;
	macho_ctrl.obj_offset = (size_t)env->ptr_start - (size_t)macho_ctrl.obj_hdr;
	if (macho_ctrl.m_num == MH_MAGIC_64
			|| macho_ctrl.m_num == MH_CIGAM_64)
	{
		otool_handle_macho_64(macho_ctrl);
	}
	else if (macho_ctrl.m_num == MH_MAGIC
			|| macho_ctrl.m_num == MH_CIGAM)
	{
		otool_handle_macho_32(macho_ctrl);
	}
	else if (!strncmp_ghetto(macho_ctrl.obj_hdr, "!<arch>\n", 8))
		otool_handle_ar(env, macho_ctrl);
}

void						handle_arch_loop_64(t_env *env, t_obj_ctrl fat_ctrl,
		struct fat_header *fat_hdr)
{
	struct fat_arch_64		*arch64;
	size_t					iter;

	iter = 0;
	write_fat_path(env);
	arch64 = (struct fat_arch_64*)(fat_ctrl.obj_hdr
			+ sizeof(struct fat_header));
	while (iter < pui32(fat_hdr->nfat_arch, fat_ctrl.m_num))
	{
		if (pui32(arch64->cputype, fat_ctrl.m_num) == CPU_TYPE_X86_64
				|| env->flags.rightcputype_found == false)
		{
			if (env->flags.rightcputype_found == false)
				write_fat_arch(env, fat_ctrl, arch64->cputype);
			env->ptr = fat_ctrl.obj_hdr + pui64(arch64->offset, fat_hdr->magic);
			handle_fat_bis(env, pui64(arch64->size, fat_ctrl.m_num));
			if (env->flags.rightcputype_found == true)
				return ;
		}
		arch64++;
		iter++;
	}
}

void						handle_arch_loop_32(t_env *env, t_obj_ctrl fat_ctrl,
		struct fat_header *fat_hdr)
{
	struct fat_arch			*arch;
	size_t					iter;

	iter = 0;
	write_fat_path(env);
	arch = (struct fat_arch*)(fat_ctrl.obj_hdr + sizeof(struct fat_header));
	while (iter < pui32(fat_hdr->nfat_arch, fat_ctrl.m_num))
	{
		if (pui32(arch->cputype, fat_ctrl.m_num) == CPU_TYPE_X86_64
				|| env->flags.rightcputype_found == false)
		{
			if (env->flags.rightcputype_found == false)
				write_fat_arch(env, fat_ctrl, arch->cputype);
			env->ptr = fat_ctrl.obj_hdr + pui32(arch->offset, fat_hdr->magic);
			handle_fat_bis(env, pui32(arch->size, fat_ctrl.m_num));
			if (env->flags.rightcputype_found == true)
				return ;
		}
		arch++;
		iter++;
	}
}
