/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_ar_object.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 13:42:55 by fdexheim          #+#    #+#             */
/*   Updated: 2018/10/04 14:14:09 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/nm.h"

static void			write_sym_path(t_env *env, char *name)
{
	write(1, "\n", 1);
	putstr_ghetto(env->path);
	write(1, "(", 1);
	putstr_ghetto(name);
	write(1, "):\n", 3);
}

void				handle_ar_object(t_env *env, struct ar_hdr *obj_hdr)
{
	t_obj_ctrl		macho_ctrl;

	write_sym_path(env, (char*)obj_hdr + sizeof(struct ar_hdr));
	macho_ctrl.obj_hdr = (char *)obj_hdr + sizeof(struct ar_hdr)
		+ get_ar_name_size(obj_hdr);
	macho_ctrl.obj_size = atoi_ghetto(obj_hdr->ar_size);
	macho_ctrl.m_num = *(uint32_t*)macho_ctrl.obj_hdr;
	macho_ctrl.obj_offset = (size_t)macho_ctrl.obj_hdr - (size_t)env->ptr_start;
	if (macho_ctrl.m_num == MH_MAGIC || macho_ctrl.m_num == MH_CIGAM)
		nm_handle_macho_32(env, macho_ctrl);
	else if (macho_ctrl.m_num == MH_MAGIC_64
			|| macho_ctrl.m_num == MH_CIGAM_64)
		nm_handle_macho_64(env, macho_ctrl);
	display(env, macho_ctrl);
	full_free_symbol_list(env);
}
