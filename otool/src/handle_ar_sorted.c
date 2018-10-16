/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_ar_sorted.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 15:33:16 by fdexheim          #+#    #+#             */
/*   Updated: 2018/10/04 15:50:06 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/otool.h"

void					handle_ar_32_sorted(t_env *env, t_obj_ctrl ar_ctrl,
		struct ar_hdr *fhdr)
{
	int					objsize;
	struct ar_hdr		*obj_hdr;

	objsize = atoi_ghetto(fhdr->ar_size) + 68;
	obj_hdr = (struct ar_hdr *)(ar_ctrl.obj_hdr + objsize);
	while ((size_t)obj_hdr < (size_t)ar_ctrl.obj_hdr + ar_ctrl.obj_size)
	{
		handle_ar_object(env, obj_hdr);
		objsize = atoi_ghetto(obj_hdr->ar_size);
		obj_hdr = (struct ar_hdr *)((char*)obj_hdr + objsize + 60);
	}
}

void					handle_ar_64_sorted(t_env *env, t_obj_ctrl ar_ctrl,
		struct ar_hdr *fhdr)
{
	int					objsize;
	struct ar_hdr		*obj_hdr;

	objsize = atoi_ghetto(fhdr->ar_size) + 68;
	obj_hdr = (struct ar_hdr *)(ar_ctrl.obj_hdr + objsize);
	while ((size_t)obj_hdr < (size_t)ar_ctrl.obj_hdr + ar_ctrl.obj_size)
	{
		handle_ar_object(env, obj_hdr);
		objsize = atoi_ghetto(obj_hdr->ar_size);
		obj_hdr = (struct ar_hdr *)((char*)obj_hdr + objsize + 60);
	}
}
