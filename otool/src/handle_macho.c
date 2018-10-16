/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_macho.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 14:49:19 by fdexheim          #+#    #+#             */
/*   Updated: 2018/10/04 15:33:26 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/otool.h"

void						otool_handle_macho_32(t_obj_ctrl macho_ctrl)
{
	struct load_command		*cmds_start;
	struct mach_header		*hdr;
	struct section			*sect;

	hdr = (struct mach_header *)macho_ctrl.obj_hdr;
	cmds_start = (struct load_command *)(macho_ctrl.obj_hdr
			+ sizeof(struct mach_header));
	sect = (struct section *)get_text_section_header(macho_ctrl, cmds_start,
			pui32(hdr->ncmds, macho_ctrl.m_num));
	if (sect != NULL)
		otool_display_32(macho_ctrl, sect);
}

void						otool_handle_macho_64(t_obj_ctrl macho_ctrl)
{
	struct load_command		*cmds_start;
	struct mach_header_64	*hdr64;
	struct section_64		*sect64;

	hdr64 = (struct mach_header_64 *)macho_ctrl.obj_hdr;
	cmds_start = (struct load_command *)(macho_ctrl.obj_hdr
			+ sizeof(struct mach_header_64));
	sect64 = (struct section_64 *)get_text_section_header(macho_ctrl,
			cmds_start, pui32(hdr64->ncmds, macho_ctrl.m_num));
	if (sect64 != NULL)
		otool_display_64(macho_ctrl, sect64);
}
