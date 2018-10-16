/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 08:56:23 by fdexheim          #+#    #+#             */
/*   Updated: 2018/10/04 09:52:24 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/otool.h"

struct mach_header_64	*get_mach_header_64(t_obj_ctrl macho_ctrl)
{
	return ((struct mach_header_64*)macho_ctrl.obj_hdr);
}

struct mach_header		*get_mach_header(t_obj_ctrl macho_ctrl)
{
	return ((struct mach_header*)macho_ctrl.obj_hdr);
}

bool					infile(t_env *env, const size_t offset)
{
	size_t				fsize;

	fsize = env->file_stats.st_size;
	if (offset > fsize)
	{
		return (false);
	}
	return (true);
}

bool					inmacho(t_obj_ctrl macho_ctrl,
		const size_t offset_inmacho)
{
	if (offset_inmacho > macho_ctrl.obj_size)
	{
		return (false);
	}
	return (true);
}

bool					is_64(const uint32_t magic_number)
{
	if (magic_number == MH_MAGIC_64 || magic_number == MH_CIGAM_64)
		return (true);
	return (false);
}
