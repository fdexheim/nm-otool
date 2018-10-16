/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_effective_letter.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 14:08:59 by fdexheim          #+#    #+#             */
/*   Updated: 2018/10/11 15:23:56 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/nm.h"

static char			get_letter_from_segname(const char *sectname, t_symbol *sym)
{
	if (strcmp_ghetto(sectname, SECT_TEXT) == 0)
		return ('T');
	else if (strcmp_ghetto(sectname, SECT_DATA) == 0)
		return ('D');
	else if (strcmp_ghetto(sectname, SECT_BSS) == 0)
		return ('B');
	else if (strcmp_ghetto(sectname, SECT_COMMON) == 0
			&& sym->n_type & N_EXT && sym->n_type & N_UNDF && sym->n_value != 0)
		return ('C');
	else
		return ('S');
}

static char			get_from_n_sect(const t_obj_ctrl macho_ctrl, t_symbol *sym)
{
	struct section_64		*sec64;
	struct section			*sec;

	sec = NULL;
	sec64 = NULL;
	if (is_64(macho_ctrl.m_num))
	{
		sec64 = get_section_from_number_64(macho_ctrl, sym->n_sect);
		return (get_letter_from_segname(sec64->sectname, sym));
	}
	else
	{
		sec = get_section_from_number(macho_ctrl, sym->n_sect);
		return (get_letter_from_segname(sec->sectname, sym));
	}
	return ('?');
}

static char			get_from_n_type(t_symbol *sym)
{
	uint8_t			a;

	a = sym->n_type & N_TYPE;
	if (a == N_UNDF && sym->n_value != 0)
		return ('C');
	else if (a == N_UNDF)
		return ('U');
	else if (a == N_ABS)
		return ('A');
	else if (a == N_PBUD)
		return ('P');
	else if (a == N_INDR)
		return ('I');
	return ('?');
}

char				calc_effective_letter(const t_obj_ctrl macho_ctrl,
		t_symbol *sym)
{
	char			ret;

	ret = '?';
	if (sym->n_type == 0 && sym->n_sect == 0)
		return ('?');
	if (sym->n_type & N_STAB)
		return ('-');
	if ((sym->n_type & N_TYPE) != N_SECT)
		ret = get_from_n_type(sym);
	else if ((sym->n_type & N_TYPE) == N_SECT)
		ret = get_from_n_sect(macho_ctrl, sym);
	else if (sym->n_type & N_PEXT)
		ret = 'E';
	else
		ret = '?';
	if (!(sym->n_type & N_EXT))
		ret = lowercase_ghetto(ret);
	return (ret);
}
