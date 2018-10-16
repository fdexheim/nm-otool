/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_fat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 14:50:22 by fdexheim          #+#    #+#             */
/*   Updated: 2018/09/24 12:29:16 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/otool.h"

bool					check_fat_64(t_env *env, t_obj_ctrl fat_ctrl)
{
	struct fat_header	*fathdr;

	if (fat_ctrl.obj_size < sizeof(struct fat_header))
		return (false);
	fathdr = (struct fat_header *)fat_ctrl.obj_hdr;
	if (check_arch_64(env, fat_ctrl, fathdr) == false)
		return (false);
	return (true);
}

bool					check_fat_32(t_env *env, t_obj_ctrl fat_ctrl)
{
	struct fat_header	*fathdr;

	if (fat_ctrl.obj_size < sizeof(struct fat_header))
		return (false);
	fathdr = (struct fat_header *)fat_ctrl.obj_hdr;
	if (check_arch_32(env, fat_ctrl, fathdr) == false)
		return (false);
	return (true);
}
