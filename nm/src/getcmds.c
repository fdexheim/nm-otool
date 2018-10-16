/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getcmds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 14:41:23 by fdexheim          #+#    #+#             */
/*   Updated: 2018/10/02 15:35:23 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/nm.h"

struct load_command			*get_cmds(t_obj_ctrl macho_ctrl,
		struct load_command *cmds_start,
		const uint32_t cmd, const uint32_t size)
{
	uint32_t				n;
	struct load_command		*cmdptr;

	n = 0;
	cmdptr = cmds_start;
	while (n < size)
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
