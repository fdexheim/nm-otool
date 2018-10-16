/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_ar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 15:33:07 by fdexheim          #+#    #+#             */
/*   Updated: 2018/10/04 16:18:10 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/otool.h"

static void				write_arch_path(t_env *env)
{
	putstr_ghetto("Archive : ");
	putstr_ghetto(env->path);
	putstr_ghetto("\n");
}

static void				handle_ar_64(t_env *env, t_obj_ctrl ar_ctrl,
		struct ar_hdr *arhdr, const bool is_sorted)
{
	struct ranlib_64	*ranlb;
	struct ranlib_64	*ranlb_start;
	size_t				i;

	i = 0;
	ranlb_start = (struct ranlib_64 *)(ar_ctrl.obj_hdr + sizeof(struct ar_hdr)
			+ get_ar_name_size(arhdr) + 16);
	ranlb = ranlb_start;
	write_arch_path(env);
	if (is_sorted == false)
	{
		while (i < *(uint64_t*)(ar_ctrl.obj_hdr + sizeof(struct ar_hdr)
					+ get_ar_name_size(arhdr) + 8))
		{
			if (check_no_ranlib_duplicates_64(ranlb_start, ranlb) == true)
				handle_ar_object(env,
						(struct ar_hdr *)(ar_ctrl.obj_hdr + ranlb->ran_off));
			i += sizeof(struct ranlib);
			ranlb++;
		}
	}
	else
		handle_ar_64_sorted(env, ar_ctrl, arhdr);
}

static void				handle_ar_32(t_env *env, t_obj_ctrl ar_ctrl,
		struct ar_hdr *arhdr, const bool is_sorted)
{
	struct ranlib		*ranlb;
	struct ranlib		*ranlb_start;
	size_t				i;

	i = 0;
	ranlb_start = (struct ranlib *)(ar_ctrl.obj_hdr + sizeof(struct ar_hdr)
			+ get_ar_name_size(arhdr) + 12);
	ranlb = ranlb_start;
	write_arch_path(env);
	if (is_sorted == false)
	{
		while (i < *(uint32_t*)(ar_ctrl.obj_hdr + sizeof(struct ar_hdr)
				+ get_ar_name_size(arhdr) + 8))
		{
			if (check_no_ranlib_duplicates(ranlb_start, ranlb) == true)
				handle_ar_object(env,
						(struct ar_hdr *)(ar_ctrl.obj_hdr + ranlb->ran_off));
			i += sizeof(struct ranlib);
			ranlb++;
		}
	}
	else
		handle_ar_32_sorted(env, ar_ctrl, arhdr);
}

void					otool_handle_ar(t_env *env, t_obj_ctrl ar_ctrl)
{
	struct ar_hdr		*arhdr;
	char				*type;

	arhdr = (struct ar_hdr*)(ar_ctrl.obj_hdr + 8);
	type = ar_ctrl.obj_hdr + 8 + sizeof(struct ar_hdr);
	if (atoi_ghetto(arhdr->ar_size) == 0)
		return ;
	if (!strncmp_ghetto(type, SYMDEF_SORTED, strlen_ghetto(SYMDEF_SORTED)))
		handle_ar_32(env, ar_ctrl, arhdr, true);
	else if (!strncmp_ghetto(type, SYMDEF, strlen_ghetto(SYMDEF)))
		handle_ar_32(env, ar_ctrl, arhdr, false);
	else if (!strncmp_ghetto(type, SYMDEF_64_SORTED,
				strlen_ghetto(SYMDEF_64_SORTED)))
		handle_ar_64(env, ar_ctrl, arhdr, true);
	else if (!strncmp_ghetto(type, SYMDEF_64, strlen_ghetto(SYMDEF_64)))
		handle_ar_64(env, ar_ctrl, arhdr, false);
}
