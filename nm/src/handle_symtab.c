/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_symtab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 12:40:42 by fdexheim          #+#    #+#             */
/*   Updated: 2018/10/10 13:36:49 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/nm.h"

static void				handle_symbol_64(t_env *env, t_obj_ctrl macho_ctrl,
		const struct nlist_64 *sym)
{
	t_symbol			*symret;

	symret = malloc(sizeof(t_symbol));
	symret->index = pui32(env->symtab_cmd->stroff, macho_ctrl.m_num)
		+ pui32(sym->n_un.n_strx, macho_ctrl.m_num);
	symret->n_strx = pui32(sym->n_un.n_strx, macho_ctrl.m_num);
	symret->n_type = sym->n_type;
	symret->n_sect = sym->n_sect;
	symret->n_desc = pui16(sym->n_desc, macho_ctrl.m_num);
	symret->n_value = pui64(sym->n_value, macho_ctrl.m_num);
	symret->bad_index = false;
	symret->name = macho_ctrl.obj_hdr
		+ pui32(env->symtab_cmd->stroff, macho_ctrl.m_num)
		+ pui32(sym->n_un.n_strx, macho_ctrl.m_num);
	if ((size_t)symret->name - (size_t)macho_ctrl.obj_hdr > macho_ctrl.obj_size)
	{
		symret->name = "bad string index";
		symret->bad_index = true;
	}
	symret->effective_letter = calc_effective_letter(macho_ctrl, symret);
	symbol_add(env, symret);
}

static void				handle_symbol_32(t_env *env, t_obj_ctrl macho_ctrl,
		const struct nlist *sym)
{
	t_symbol			*symret;

	symret = malloc(sizeof(t_symbol));
	symret->index = pui32(env->symtab_cmd->stroff, macho_ctrl.m_num)
		+ pui32(sym->n_un.n_strx, macho_ctrl.m_num);
	symret->n_strx = pui32(sym->n_un.n_strx, macho_ctrl.m_num);
	symret->n_type = sym->n_type;
	symret->n_sect = sym->n_sect;
	symret->n_desc = pui16(sym->n_desc, macho_ctrl.m_num);
	symret->n_value = pui32(sym->n_value, macho_ctrl.m_num);
	symret->bad_index = false;
	symret->name = macho_ctrl.obj_hdr
		+ pui32(env->symtab_cmd->stroff, macho_ctrl.m_num)
		+ pui32(sym->n_un.n_strx, macho_ctrl.m_num);
	if ((size_t)symret->name - (size_t)macho_ctrl.obj_hdr > macho_ctrl.obj_size)
	{
		symret->name = "bad string index";
		symret->bad_index = true;
	}
	symret->effective_letter = calc_effective_letter(macho_ctrl, symret);
	symbol_add(env, symret);
}

static void				handle_symtab_64(t_env *env, t_obj_ctrl macho_ctrl)
{
	struct nlist_64		*sym;
	uint32_t			i;

	if (env->syms_start == NULL)
		return ;
	sym = (struct nlist_64*)(env->syms_start);
	i = 0;
	while (i < pui32(env->symtab_cmd->nsyms, macho_ctrl.m_num))
	{
		handle_symbol_64(env, macho_ctrl, sym);
		sym++;
		i++;
	}
}

static void				handle_symtab_32(t_env *env, t_obj_ctrl macho_ctrl)
{
	struct nlist		*sym;
	uint32_t			i;

	if (env->syms_start == NULL)
		return ;
	sym = (struct nlist*)(env->syms_start);
	i = 0;
	while (i < pui32(env->symtab_cmd->nsyms, macho_ctrl.m_num))
	{
		handle_symbol_32(env, macho_ctrl, sym);
		sym++;
		i++;
	}
}

void					handle_symtab(t_env *env, t_obj_ctrl macho_ctrl)
{
	if (macho_ctrl.m_num == MH_MAGIC_64 || macho_ctrl.m_num == MH_CIGAM_64)
		handle_symtab_64(env, macho_ctrl);
	else if (macho_ctrl.m_num == MH_MAGIC || macho_ctrl.m_num == MH_CIGAM)
		handle_symtab_32(env, macho_ctrl);
}
