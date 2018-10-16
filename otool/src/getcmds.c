/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getcmds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 14:41:23 by fdexheim          #+#    #+#             */
/*   Updated: 2018/10/04 08:57:56 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/otool.h"

static void					*get_text_section_from_segment_32(
		t_obj_ctrl macho_ctrl, struct segment_command *seg)
{
	uint32_t				n;
	struct section			*sect;

	n = 0;
	sect = (struct section *)((void *)seg + sizeof(struct segment_command));
	while (n < pui32(seg->nsects, macho_ctrl.m_num))
	{
		if (!strcmp_ghetto(sect->segname, SEG_TEXT)
				&& !strcmp_ghetto(sect->sectname, SECT_TEXT))
			return (sect);
		n++;
	}
	return (NULL);
}

static void					*get_text_section_from_segment_64(
		t_obj_ctrl macho_ctrl, struct segment_command_64 *seg64)
{
	uint32_t				n;
	struct section_64		*sect64;

	n = 0;
	sect64 = (struct section_64 *)((void *)seg64
			+ sizeof(struct segment_command_64));
	while (n < pui32(seg64->nsects, macho_ctrl.m_num))
	{
		if (!strcmp_ghetto(sect64->segname, SEG_TEXT)
				&& !strcmp_ghetto(sect64->sectname, SECT_TEXT))
			return (sect64);
		n++;
	}
	return (NULL);
}

void						*get_text_section_header(t_obj_ctrl macho_ctrl,
		struct load_command *cmdptr, const uint32_t ncmds)
{
	uint32_t				n;

	n = 0;
	while (n < ncmds)
	{
		if (pui32(cmdptr->cmd, macho_ctrl.m_num) == LC_SEGMENT_64)
		{
			if (get_text_section_from_segment_64(macho_ctrl,
						(struct segment_command_64*)cmdptr) != NULL)
				return (get_text_section_from_segment_64(macho_ctrl,
							(struct segment_command_64*)cmdptr));
		}
		else if (pui32(cmdptr->cmd, macho_ctrl.m_num) == LC_SEGMENT)
		{
			if (get_text_section_from_segment_32(macho_ctrl,
						(struct segment_command*)cmdptr) != NULL)
				return (get_text_section_from_segment_32(macho_ctrl,
						(struct segment_command *)cmdptr));
		}
		n++;
		cmdptr = (struct load_command *)(((unsigned char*)cmdptr)
				+ pui32(cmdptr->cmdsize, macho_ctrl.m_num));
	}
	return (NULL);
}

struct load_command			*get_cmds(t_obj_ctrl macho_ctrl,
		struct load_command *cmds_start,
		const uint32_t cmd, const uint32_t ncmds)
{
	uint32_t				n;
	struct load_command		*cmdptr;

	n = 0;
	cmdptr = cmds_start;
	while (n < ncmds)
	{
		if (pui32(cmdptr->cmd, macho_ctrl.m_num) == cmd)
		{
			return (struct load_command *)cmdptr;
		}
		n++;
		cmdptr = (struct load_command *)(((unsigned char*)cmdptr)
				+ pui32(cmdptr->cmdsize, macho_ctrl.m_num));
	}
	return (NULL);
}
