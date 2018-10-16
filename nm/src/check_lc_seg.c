/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_lc_seg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 14:52:17 by fdexheim          #+#    #+#             */
/*   Updated: 2018/10/10 13:37:43 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/nm.h"

static bool				check_lc_seg_32(struct mach_header *hdr,
		struct segment_command *seg, t_obj_ctrl macho_ctrl)
{
	struct section		*sect;
	size_t				i;

	i = 0;
	if (pui32(seg->cmdsize, macho_ctrl.m_num)
			!= (sizeof(struct segment_command) + pui32(seg->nsects,
					macho_ctrl.m_num) * sizeof(struct section)))
		return (false);
	sect = (struct section *)((char *)seg + sizeof(struct segment_command));
	while (i < pui32(seg->nsects, macho_ctrl.m_num))
	{
		if (pui32(sect->offset, macho_ctrl.m_num) < pui32(hdr->sizeofcmds,
					macho_ctrl.m_num) + sizeof(struct mach_header)
			|| pui32(sect->offset, macho_ctrl.m_num) < pui32(hdr->sizeofcmds,
				macho_ctrl.m_num) + sizeof(struct mach_header)
			|| pui32(sect->offset, macho_ctrl.m_num) + pui32(sect->size,
				macho_ctrl.m_num) > macho_ctrl.obj_size)
		{
			return (false);
		}
		seg++;
		i++;
	}
	return (true);
}

static bool				check_lc_seg_64(struct mach_header_64 *hdr64,
		struct segment_command_64 *seg, t_obj_ctrl macho_ctrl)
{
	struct section_64	*sect;
	size_t				i;

	i = 0;
	if (pui32(seg->cmdsize, macho_ctrl.m_num)
			!= (sizeof(struct segment_command_64) + pui32(seg->nsects,
					macho_ctrl.m_num) * sizeof(struct section_64)))
		return (false);
	sect = (struct section_64 *)((char *)seg
			+ sizeof(struct segment_command_64));
	while (i < pui32(seg->nsects, macho_ctrl.m_num))
	{
		if (pui32(sect->offset, macho_ctrl.m_num) < pui32(hdr64->sizeofcmds,
				macho_ctrl.m_num) + sizeof(struct mach_header)
			|| pui32(sect->offset, macho_ctrl.m_num) < pui32(hdr64->sizeofcmds,
				macho_ctrl.m_num) + sizeof(struct mach_header)
			|| pui32(sect->offset, macho_ctrl.m_num) + pui64(sect->size,
				macho_ctrl.m_num) > macho_ctrl.obj_size)
			return (false);
		seg++;
		i++;
	}
	return (true);
}

bool					check_lc_seg_tab_32(struct mach_header *hdr,
		struct load_command *cmds_start, t_obj_ctrl macho_ctrl)
{
	struct load_command		*cmdptr;
	struct segment_command	*segcmd;
	uint32_t				ncmd;

	ncmd = 0;
	cmdptr = cmds_start;
	while (ncmd < pui32(hdr->ncmds, macho_ctrl.m_num))
	{
		if (cmdptr->cmd == LC_SEGMENT)
		{
			segcmd = (struct segment_command*)cmdptr;
			if (pui32(segcmd->fileoff, macho_ctrl.m_num)
					+ pui32(segcmd->filesize, macho_ctrl.m_num)
					> macho_ctrl.obj_size
					|| check_lc_seg_32(hdr, segcmd, macho_ctrl) == false)
			{
				return (false);
			}
		}
		cmdptr = (struct load_command*)((char *)cmdptr + pui32(cmdptr->cmdsize,
					macho_ctrl.m_num));
		ncmd++;
	}
	return (true);
}

bool					check_lc_seg_tab_64(struct mach_header_64 *hdr64,
		struct load_command *cmds_start, t_obj_ctrl macho_ctrl)
{
	struct load_command			*cmdptr;
	struct segment_command_64	*segcmd64;
	uint32_t					ncmd;

	ncmd = 0;
	cmdptr = cmds_start;
	while (ncmd < pui32(hdr64->ncmds, macho_ctrl.m_num))
	{
		if (cmdptr->cmd == LC_SEGMENT_64)
		{
			segcmd64 = (struct segment_command_64*)cmdptr;
			if (pui64(segcmd64->fileoff, macho_ctrl.m_num)
					+ pui64(segcmd64->filesize, macho_ctrl.m_num)
					> macho_ctrl.obj_size
					|| check_lc_seg_64(hdr64, segcmd64, macho_ctrl) == false)
			{
				return (false);
			}
		}
		cmdptr = (struct load_command*)((char *)cmdptr + pui32(cmdptr->cmdsize,
					macho_ctrl.m_num));
		ncmd++;
	}
	return (true);
}
