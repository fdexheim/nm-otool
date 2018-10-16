/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arch.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 10:43:48 by fdexheim          #+#    #+#             */
/*   Updated: 2018/10/10 14:22:24 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/nm.h"

static bool				check_arch_bis(t_env *env, t_obj_ctrl macho_ctrl)
{
	macho_ctrl.m_num = *(int *)macho_ctrl.obj_hdr;
	if (macho_ctrl.m_num == MH_MAGIC_64
			|| macho_ctrl.m_num == MH_CIGAM_64)
		return (check_macho_64(env, macho_ctrl));
	else if (macho_ctrl.m_num == MH_MAGIC
			|| macho_ctrl.m_num == MH_CIGAM)
		return (check_macho_32(env, macho_ctrl));
	else if (!strncmp_ghetto(env->ptr_start, "!<arch>\n", 8))
		return (check_ar(env, macho_ctrl));
	return (true);
}

static bool				check_arch_64_loop(t_env *env, t_obj_ctrl fat_ctrl,
		struct fat_arch_64 *arch64, const uint32_t iter)
{
	size_t				i;
	t_obj_ctrl			macho_ctrl;

	i = 0;
	while (i < iter)
	{
		if (pui32(arch64->cputype, fat_ctrl.m_num) == CPU_TYPE_X86_64)
			env->flags.right_cputype_found = true;
		macho_ctrl.obj_size = pui32(arch64->size, fat_ctrl.m_num);
		macho_ctrl.obj_offset = pui32(arch64->offset, fat_ctrl.m_num);
		macho_ctrl.obj_hdr = fat_ctrl.obj_hdr + macho_ctrl.obj_offset;
		if (macho_ctrl.obj_offset > fat_ctrl.obj_size
				|| macho_ctrl.obj_offset + macho_ctrl.obj_size
				> fat_ctrl.obj_size || !check_arch_bis(env, macho_ctrl))
			return (false);
		arch64++;
		i++;
	}
	return (true);
}

bool					check_arch_64(t_env *env, t_obj_ctrl fat_ctrl,
		struct fat_header *fathdr)
{
	struct fat_arch_64	*arch64;

	if (sizeof(struct fat_header) + sizeof(struct fat_arch_64)
			* pui32(fathdr->nfat_arch, fathdr->magic) > fat_ctrl.obj_size)
		return (false);
	arch64 = (struct fat_arch_64 *)(env->ptr_start + sizeof(struct fat_header));
	return (check_arch_64_loop(env, fat_ctrl, arch64, pui32(fathdr->nfat_arch,
					fathdr->magic)));
}

static bool				check_arch_32_loop(t_env *env, t_obj_ctrl fat_ctrl,
		struct fat_arch *arch, const uint32_t iter)
{
	size_t				i;
	t_obj_ctrl			macho_ctrl;

	i = 0;
	while (i < iter)
	{
		if (pui32(arch->cputype, fat_ctrl.m_num) == CPU_TYPE_X86_64)
			env->flags.right_cputype_found = true;
		macho_ctrl.obj_size = pui32(arch->size, fat_ctrl.m_num);
		macho_ctrl.obj_offset = pui32(arch->offset, fat_ctrl.m_num);
		macho_ctrl.obj_hdr = fat_ctrl.obj_hdr + macho_ctrl.obj_offset;
		if (macho_ctrl.obj_offset > fat_ctrl.obj_size
				|| macho_ctrl.obj_offset + macho_ctrl.obj_size
				> fat_ctrl.obj_size || !check_arch_bis(env, macho_ctrl))
			return (false);
		arch++;
		i++;
	}
	return (true);
}

bool					check_arch_32(t_env *env, t_obj_ctrl fat_ctrl,
		struct fat_header *fathdr)
{
	struct fat_arch		*arch;

	if (sizeof(struct fat_header) + sizeof(struct fat_arch)
			* pui32(fathdr->nfat_arch, fathdr->magic) > fat_ctrl.obj_size)
		return (false);
	arch = (struct fat_arch *)(env->ptr_start + sizeof(struct fat_header));
	return (check_arch_32_loop(env, fat_ctrl, arch, pui32(fathdr->nfat_arch,
					fathdr->magic)));
}
