/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_section.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/25 13:51:09 by fdexheim          #+#    #+#             */
/*   Updated: 2018/10/04 08:57:17 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/otool.h"

static struct section_64		*get_section_from_number_segment_64(
		struct segment_command_64 *cmd, const uint8_t num)
{
	uint8_t						i;
	struct section_64			*ret;

	i = 1;
	ret = (struct section_64 *)((unsigned char*)cmd
			+ sizeof(struct segment_command_64));
	while (i < num)
	{
		ret++;
		i++;
	}
	return (ret);
}

struct section_64				*get_section_from_number_64(
		t_obj_ctrl macho_ctrl, const uint8_t num)
{
	uint8_t						i;
	uint32_t					nc;
	struct load_command			*cmds;
	struct segment_command_64	*seg;

	i = 0;
	nc = 0;
	cmds = (struct load_command*)((unsigned char *)macho_ctrl.obj_hdr
			+ sizeof(struct mach_header_64));
	while (nc < pui32(get_mach_header(macho_ctrl)->ncmds, macho_ctrl.m_num))
	{
		if (pui32(cmds->cmd, macho_ctrl.m_num) == LC_SEGMENT_64)
		{
			seg = (struct segment_command_64 *)cmds;
			if (i + pui32(seg->nsects, macho_ctrl.m_num) >= num)
				return (get_section_from_number_segment_64(seg, num - i));
			i += pui32(seg->nsects, macho_ctrl.m_num);
		}
		cmds = (struct load_command *)((unsigned char *)cmds
				+ pui32(cmds->cmdsize, macho_ctrl.m_num));
		nc++;
	}
	return (NULL);
}

static struct section			*get_section_from_number_segment(
		struct segment_command *cmd, const uint8_t num)
{
	uint8_t						i;
	struct section				*ret;

	i = 1;
	ret = (struct section *)((unsigned char*)cmd
			+ sizeof(struct segment_command));
	while (i < num)
	{
		ret++;
		i++;
	}
	return (ret);
}

struct section					*get_section_from_number(t_obj_ctrl macho_ctrl,
		const uint8_t num)
{
	uint8_t						i;
	uint32_t					nc;
	struct load_command			*cmd;
	struct segment_command		*seg;

	i = 0;
	nc = 0;
	cmd = (struct load_command*)((unsigned char *)macho_ctrl.obj_hdr
			+ sizeof(struct mach_header));
	while (nc < pui32(get_mach_header(macho_ctrl)->ncmds, macho_ctrl.m_num))
	{
		if (pui32(cmd->cmd, macho_ctrl.m_num) == LC_SEGMENT)
		{
			seg = (struct segment_command *)cmd;
			if (i + pui32(seg->nsects, macho_ctrl.m_num) >= num)
				return (get_section_from_number_segment(seg, num - i));
			i += pui32(seg->nsects, macho_ctrl.m_num);
		}
		cmd = (struct load_command *)((unsigned char *)cmd
				+ pui32(cmd->cmdsize, macho_ctrl.m_num));
		nc++;
	}
	return (NULL);
}
