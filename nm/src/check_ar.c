/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ar.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 13:06:18 by fdexheim          #+#    #+#             */
/*   Updated: 2018/10/10 13:37:29 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/nm.h"

static bool			check_ar_64(t_env *env, struct ar_hdr *arhdr,
		t_obj_ctrl statlib_ctrl)
{
	size_t				symtab_size;
	struct ranlib_64	*ranlb;
	size_t				i;

	i = 0;
	symtab_size = *(uint32_t*)(statlib_ctrl.obj_hdr + sizeof(struct ar_hdr)
			+ get_ar_name_size(arhdr) + 8);
	ranlb = (struct ranlib_64 *)(statlib_ctrl.obj_hdr + sizeof(struct ar_hdr)
			+ get_ar_name_size(arhdr) + 16);
	if ((size_t)ranlb + sizeof(struct ranlib) * symtab_size
			> (size_t)statlib_ctrl.obj_hdr + statlib_ctrl.obj_size)
		return (false);
	if (symtab_size % sizeof(struct ranlib) != 0)
		return (false);
	while (i < symtab_size)
	{
		if (check_ar_objects(env,
					(struct ar_hdr *)(statlib_ctrl.obj_hdr
						+ ranlb->ran_off)) == false)
			return (false);
		ranlb++;
	}
	return (true);
}

static bool			check_ar_32(t_env *env, struct ar_hdr *arhdr,
		t_obj_ctrl statlib_ctrl)
{
	size_t			symtab_size;
	struct ranlib	*ranlb;
	size_t			i;

	i = 0;
	symtab_size = *(uint32_t*)(statlib_ctrl.obj_hdr + sizeof(struct ar_hdr)
			+ get_ar_name_size(arhdr) + 8);
	ranlb = (struct ranlib *)(statlib_ctrl.obj_hdr + sizeof(struct ar_hdr)
			+ get_ar_name_size(arhdr) + 12);
	if ((size_t)ranlb + sizeof(struct ranlib) * symtab_size
			> (size_t)statlib_ctrl.obj_hdr + statlib_ctrl.obj_size)
		return (false);
	if (symtab_size % sizeof(struct ranlib) != 0)
		return (false);
	while (i < symtab_size)
	{
		if (check_ar_objects(env,
					(struct ar_hdr *)(statlib_ctrl.obj_hdr
						+ ranlb->ran_off)) == false)
			return (false);
		ranlb++;
		i += sizeof(struct ranlib);
	}
	return (true);
}

bool				check_ar(t_env *env, t_obj_ctrl statlib_ctrl)
{
	struct ar_hdr	*arhdr;
	char			*type;

	arhdr = (struct ar_hdr*)(statlib_ctrl.obj_hdr + 8);
	type = statlib_ctrl.obj_hdr + 8 + sizeof(struct ar_hdr);
	if (atoi_ghetto(arhdr->ar_size) == 0)
		return (true);
	if (!infile(env, statlib_ctrl.obj_offset + statlib_ctrl.obj_size))
		return (false);
	if (statlib_ctrl.obj_size < sizeof(struct ar_hdr) + 8)
		return (false);
	if (!strncmp_ghetto(type, SYMDEF, strlen_ghetto(SYMDEF))
			|| !strncmp_ghetto(type, SYMDEF_SORTED,
				strlen_ghetto(SYMDEF_SORTED)))
	{
		return (check_ar_32(env, arhdr, statlib_ctrl));
	}
	else if (!strncmp_ghetto(type, SYMDEF_64, strlen_ghetto(SYMDEF_64))
			|| !strncmp_ghetto(type, SYMDEF_64_SORTED,
				strlen_ghetto(SYMDEF_64_SORTED)))
	{
		return (check_ar_64(env, arhdr, statlib_ctrl));
	}
	return (false);
}
