/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_lc_tab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 14:51:11 by fdexheim          #+#    #+#             */
/*   Updated: 2018/10/04 08:37:38 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/otool.h"

static bool				check_tab_size_to_section_32(
		const size_t sizeofcmds, t_obj_ctrl macho_ctrl)
{
	struct section		*sec;
	size_t				section_offset;
	size_t				toffset;

	toffset = sizeof(struct mach_header) + sizeofcmds;
	section_offset = 0;
	sec = get_section_from_number(macho_ctrl, 1);
	if (sec == NULL)
		return (false);
	section_offset = pui32(sec->offset, macho_ctrl.m_num);
	if (toffset > section_offset || toffset > macho_ctrl.obj_size)
	{
		return (false);
	}
	return (true);
}

static bool				check_tab_size_to_section_64(
		const size_t sizeofcmds, t_obj_ctrl macho_ctrl)
{
	struct section_64	*sec64;
	size_t				section_offset;
	size_t				toffset;

	toffset = sizeof(struct mach_header_64) + sizeofcmds;
	section_offset = 0;
	sec64 = get_section_from_number_64(macho_ctrl, 1);
	if (sec64 == NULL)
	{
		return (false);
	}
	section_offset = pui32(sec64->offset, macho_ctrl.m_num);
	if (toffset > section_offset || toffset > macho_ctrl.obj_size)
	{
		return (false);
	}
	return (true);
}

bool					check_lctab_32(struct mach_header *hdr,
		struct load_command *cmds_start, t_obj_ctrl macho_ctrl)
{
	uint32_t			ncmds_control;
	uint32_t			scmds_control;
	struct load_command	*cmdptr;

	ncmds_control = 0;
	scmds_control = 0;
	cmdptr = cmds_start;
	while (ncmds_control < pui32(hdr->ncmds, macho_ctrl.m_num))
	{
		scmds_control += pui32(cmdptr->cmdsize, macho_ctrl.m_num);
		ncmds_control++;
		if (scmds_control > pui32(hdr->sizeofcmds, macho_ctrl.m_num)
			|| scmds_control + sizeof(struct mach_header) > macho_ctrl.obj_size)
			return (false);
		cmdptr = (struct load_command *)((unsigned char *)(cmdptr)
				+ pui32(cmdptr->cmdsize, macho_ctrl.m_num));
	}
	if (scmds_control != pui32(hdr->sizeofcmds, macho_ctrl.m_num))
		return (false);
	return (check_tab_size_to_section_32(pui32(hdr->sizeofcmds,
					macho_ctrl.m_num), macho_ctrl));
}

bool					check_lctab_64(struct mach_header_64 *hdr64,
		struct load_command *cmds_start, t_obj_ctrl macho_ctrl)
{
	uint32_t			ncmds_control;
	uint32_t			scmds_control;
	struct load_command	*cmdptr;

	ncmds_control = 0;
	scmds_control = 0;
	cmdptr = cmds_start;
	while (ncmds_control < pui32(hdr64->ncmds, macho_ctrl.m_num))
	{
		scmds_control += pui32(cmdptr->cmdsize, macho_ctrl.m_num);
		ncmds_control++;
		if (scmds_control > pui32(hdr64->sizeofcmds, macho_ctrl.m_num)
				|| scmds_control + sizeof(struct mach_header_64)
				> macho_ctrl.obj_size)
			return (false);
		cmdptr = (struct load_command *)((unsigned char *)(cmdptr)
			+ pui32(cmdptr->cmdsize, macho_ctrl.m_num));
	}
	if (scmds_control != pui32(hdr64->sizeofcmds, macho_ctrl.m_num))
		return (false);
	return (check_tab_size_to_section_64(pui32(hdr64->sizeofcmds,
					macho_ctrl.m_num), macho_ctrl));
}
