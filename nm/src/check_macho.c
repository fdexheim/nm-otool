/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_macho.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 12:44:27 by fdexheim          #+#    #+#             */
/*   Updated: 2018/10/10 15:58:50 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/nm.h"

bool				check_macho_64(t_env *env, t_obj_ctrl macho_ctrl)
{
	struct load_command		*cmds_start;
	struct mach_header_64	*hdr64;

	hdr64 = (struct mach_header_64 *)macho_ctrl.obj_hdr;
	cmds_start = (struct load_command *)(macho_ctrl.obj_hdr
			+ sizeof(struct mach_header_64));
	if (check_lctab_64((struct mach_header_64 *)macho_ctrl.obj_hdr,
			cmds_start, macho_ctrl) == false
		|| check_lc_seg_tab_64((struct mach_header_64*)macho_ctrl.obj_hdr,
			cmds_start, macho_ctrl) == false)
		return (false);
	env->symtab_cmd = (struct symtab_command *)get_cmds(macho_ctrl, cmds_start,
		LC_SYMTAB, pui32(hdr64->ncmds, macho_ctrl.m_num));
	if (env->symtab_cmd == NULL)
		return (false);
	env->syms_start = (void*)((unsigned char*)hdr64
		+ pui32(env->symtab_cmd->symoff, macho_ctrl.m_num));
	return (check_symtab(env, macho_ctrl));
}

bool				check_macho_32(t_env *env, t_obj_ctrl macho_ctrl)
{
	struct load_command		*cmds_start;
	struct mach_header		*hdr;

	hdr = (struct mach_header *)macho_ctrl.obj_hdr;
	cmds_start = (struct load_command *)(macho_ctrl.obj_hdr
		+ sizeof(struct mach_header));
	if (check_lctab_32((struct mach_header *)macho_ctrl.obj_hdr,
		cmds_start, macho_ctrl) == false
			|| check_lc_seg_tab_32((struct mach_header*)macho_ctrl.obj_hdr,
				cmds_start, macho_ctrl) == false)
		return (false);
	env->symtab_cmd = (struct symtab_command *)get_cmds(macho_ctrl, cmds_start,
		LC_SYMTAB, pui32(hdr->ncmds, macho_ctrl.m_num));
	if (env->symtab_cmd == NULL)
		return (false);
	env->syms_start = (void*)((unsigned char*)hdr
		+ pui32(env->symtab_cmd->symoff, macho_ctrl.m_num));
	return (check_symtab(env, macho_ctrl));
}
