/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/26 14:04:06 by fdexheim          #+#    #+#             */
/*   Updated: 2018/10/04 10:02:01 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/otool.h"

static void				write_contents(void)
{
	putstr_ghetto("Contents of (__TEXT,__text) section");
}

static size_t			calc_spacing(t_obj_ctrl macho_ctrl,
		struct section *sect)
{
	uint32_t			flags;
	uint32_t			sectype;

	flags = pui32(sect->flags, macho_ctrl.m_num);
	sectype = flags & SECTION_TYPE;
	if (sectype == S_REGULAR || sectype == S_ZEROFILL
			|| sectype == S_CSTRING_LITERALS || sectype == S_LITERAL_POINTERS)
		return (1);
	else if (sectype == S_4BYTE_LITERALS)
		return (4);
	else if (sectype == S_8BYTE_LITERALS)
		return (8);
	return (1);
}

void					otool_display_64(t_obj_ctrl macho_ctrl,
		struct section_64 *sect64)
{
	size_t				i;
	char				*c;

	i = 0;
	c = macho_ctrl.obj_hdr + pui32(sect64->offset, macho_ctrl.m_num);
	write_contents();
	while (i < pui64(sect64->size, macho_ctrl.m_num))
	{
		if (i % 16 == 0)
		{
			write(1, "\n", 1);
			print_full_number_64(sect64->addr + i);
			write(1, "\t", 1);
		}
		put_unsigned_char_ghetto_hex(*c);
		write(1, " ", 1);
		i++;
		c++;
	}
	write(1, "\n", 1);
}

void					otool_display_32(t_obj_ctrl macho_ctrl,
		struct section *sect)
{
	size_t				i;
	char				*c;
	size_t				spacing;

	i = 0;
	spacing = calc_spacing(macho_ctrl, sect);
	c = macho_ctrl.obj_hdr + pui32(sect->offset, macho_ctrl.m_num);
	write_contents();
	while (i < pui32(sect->size, macho_ctrl.m_num))
	{
		if (i % 16 == 0)
		{
			write(1, "\n", 1);
			print_full_number_32(pui32(sect->addr, macho_ctrl.m_num) + i);
			write(1, "\t", 1);
		}
		put_unsigned_char_ghetto_hex(*c);
		i++;
		c++;
		if (i % spacing == 0)
			write(1, " ", 1);
	}
	write(1, "\n", 1);
}
