/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_macho.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 14:49:19 by fdexheim          #+#    #+#             */
/*   Updated: 2018/10/10 13:37:21 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/nm.h"

void						nm_handle_macho_32(t_env *env,
		t_obj_ctrl macho_ctrl)
{
	struct load_command		*cmds_start;
	struct mach_header		*hdr;

	hdr = (struct mach_header *)macho_ctrl.obj_hdr;
	cmds_start = (struct load_command *)(macho_ctrl.obj_hdr
			+ sizeof(struct mach_header));
	env->symtab_cmd = (struct symtab_command *)get_cmds(macho_ctrl, cmds_start,
			LC_SYMTAB, pui32(hdr->ncmds, macho_ctrl.m_num));
	if (env->symtab_cmd != NULL)
		env->syms_start = (void*)((unsigned char*)hdr
				+ pui32(env->symtab_cmd->symoff, macho_ctrl.m_num));
	handle_symtab(env, macho_ctrl);
}

void						nm_handle_macho_64(t_env *env,
		t_obj_ctrl macho_ctrl)
{
	struct load_command		*cmds_start;
	struct mach_header_64	*hdr64;

	hdr64 = (struct mach_header_64 *)macho_ctrl.obj_hdr;
	cmds_start = (struct load_command *)(macho_ctrl.obj_hdr
			+ sizeof(struct mach_header_64));
	env->symtab_cmd = (struct symtab_command *)get_cmds(macho_ctrl, cmds_start,
			LC_SYMTAB, pui32(hdr64->ncmds, macho_ctrl.m_num));
	if (env->symtab_cmd != NULL)
		env->syms_start = (void*)((unsigned char*)hdr64
				+ pui32(env->symtab_cmd->symoff, macho_ctrl.m_num));
	handle_symtab(env, macho_ctrl);
}
