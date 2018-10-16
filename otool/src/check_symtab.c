/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_symtab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 12:13:05 by fdexheim          #+#    #+#             */
/*   Updated: 2018/10/11 09:43:10 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/otool.h"

static bool				check_latest_string(t_obj_ctrl macho_ctrl,
		const size_t latest_string_offset)
{
	size_t				offset;
	char				*ptr;

	offset = latest_string_offset;
	ptr = (char *)(macho_ctrl.obj_hdr + latest_string_offset);
	while (offset < macho_ctrl.obj_size)
	{
		if (*ptr == 0)
			return (true);
		ptr++;
		offset++;
	}
	return (false);
}

static bool				check_symtab_64(t_env *env, t_obj_ctrl macho_ctrl)
{
	struct nlist_64		*sym;
	uint32_t			i;
	size_t				str_offset;
	size_t				latest_string_offset;

	if (env->syms_start == NULL)
		return (true);
	sym = (struct nlist_64*)(env->syms_start);
	i = 0;
	latest_string_offset = 0;
	while (i < pui32(env->symtab_cmd->nsyms, macho_ctrl.m_num))
	{
		str_offset = pui32(env->symtab_cmd->stroff, macho_ctrl.m_num)
			+ pui32(sym->n_un.n_strx, macho_ctrl.m_num);
		if (str_offset > macho_ctrl.obj_size)
			return (false);
		else if (str_offset > latest_string_offset)
			latest_string_offset = str_offset;
		sym++;
		i++;
	}
	return (check_latest_string(macho_ctrl, latest_string_offset));
}

static bool				check_symtab_32(t_env *env, t_obj_ctrl macho_ctrl)
{
	struct nlist		*sym;
	uint32_t			i;
	size_t				str_offset;
	size_t				latest_string_offset;

	if (env->syms_start == NULL)
		return (true);
	sym = (struct nlist*)(env->syms_start);
	i = 0;
	latest_string_offset = 0;
	while (i < pui32(env->symtab_cmd->nsyms, macho_ctrl.m_num))
	{
		str_offset = pui32(env->symtab_cmd->stroff, macho_ctrl.m_num)
			+ pui32(sym->n_un.n_strx, macho_ctrl.m_num);
		if (str_offset > macho_ctrl.obj_size)
			return (false);
		else if (str_offset > latest_string_offset)
			latest_string_offset = str_offset;
		sym++;
		i++;
	}
	return (check_latest_string(macho_ctrl, latest_string_offset));
}

bool					check_symtab(t_env *env, t_obj_ctrl macho_ctrl)
{
	if (macho_ctrl.m_num == MH_MAGIC_64 || macho_ctrl.m_num == MH_CIGAM_64)
		return (check_symtab_64(env, macho_ctrl));
	else if (macho_ctrl.m_num == MH_MAGIC || macho_ctrl.m_num == MH_CIGAM)
		return (check_symtab_32(env, macho_ctrl));
	return (true);
}
