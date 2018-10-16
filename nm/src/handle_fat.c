/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 13:10:33 by fdexheim          #+#    #+#             */
/*   Updated: 2018/09/24 10:16:40 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/nm.h"

void						nm_handle_fat_32(t_env *env, t_obj_ctrl fat_ctrl)
{
	struct fat_header		*fat_hdr;

	fat_ctrl.m_num = *(uint32_t*)env->ptr;
	fat_ctrl.obj_hdr = (struct fat_header*)env->ptr;
	fat_ctrl.obj_offset = (size_t)fat_ctrl.obj_hdr - (size_t)env->ptr_start;
	fat_hdr = (struct fat_header *)fat_ctrl.obj_hdr;
	handle_arch_loop_32(env, fat_ctrl, fat_hdr);
}

void						nm_handle_fat_64(t_env *env, t_obj_ctrl fat_ctrl)
{
	struct fat_header		*fat_hdr;

	fat_ctrl.m_num = *(uint32_t*)env->ptr;
	fat_ctrl.obj_hdr = (struct fat_header*)env->ptr;
	fat_ctrl.obj_offset = (size_t)fat_ctrl.obj_hdr - (size_t)env->ptr_start;
	fat_hdr = (struct fat_header *)fat_ctrl.obj_hdr;
	handle_arch_loop_64(env, fat_ctrl, fat_hdr);
}
