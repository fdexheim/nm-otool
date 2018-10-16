/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ar_objects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 15:32:43 by fdexheim          #+#    #+#             */
/*   Updated: 2018/10/04 15:32:44 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/otool.h"

bool			check_ar_objects(t_env *env, struct ar_hdr *obj_hdr)
{
	t_obj_ctrl	macho_ctrl;

	if (!infile(env, (size_t)obj_hdr + 60
				+ atoi_ghetto(obj_hdr->ar_size) - (size_t)env->ptr_start))
		return (false);
	macho_ctrl.obj_hdr = (char *)obj_hdr + sizeof(struct ar_hdr)
		+ get_ar_name_size(obj_hdr);
	macho_ctrl.obj_size = atoi_ghetto(obj_hdr->ar_size);
	macho_ctrl.obj_offset = (size_t)macho_ctrl.obj_hdr - (size_t)env->ptr_start;
	macho_ctrl.m_num = *(uint32_t*)macho_ctrl.obj_hdr;
	if (macho_ctrl.m_num == MH_MAGIC || macho_ctrl.m_num == MH_CIGAM)
		return (check_macho_32(env, macho_ctrl));
	else if (macho_ctrl.m_num == MH_MAGIC_64
			|| macho_ctrl.m_num == MH_CIGAM_64)
		return (check_macho_64(env, macho_ctrl));
	else
		return (true);
}
