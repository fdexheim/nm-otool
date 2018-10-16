/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol_list_add.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 09:14:41 by fdexheim          #+#    #+#             */
/*   Updated: 2018/10/10 15:10:06 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/nm.h"

static void			symbol_add_alphabetic(t_env *env, t_symbol *add)
{
	t_symbol		*sym;
	t_symbol		*symnext;

	if (smbcmp_name(env->symbol_list, add) > 0
		|| (smbcmp_name(env->symbol_list, add) == 0
			&& smbcmp_value(env->symbol_list, add) > 0))
	{
		symbol_add_first(env, add);
		return ;
	}
	sym = env->symbol_list;
	symnext = env->symbol_list->next;
	while (symnext != NULL && ((smbcmp_name(symnext, add) < 0)
		|| (smbcmp_name(symnext, add) == 0 && smbcmp_value(symnext, add) < 0)))
	{
		sym = symnext;
		symnext = symnext->next;
	}
	sym->next = add;
	add->next = symnext;
}

void				symbol_add(t_env *env, t_symbol *add)
{
	if (env->symbol_list == NULL)
		symbol_add_first(env, add);
	else
	{
		if (env->flags.p == true)
			symbol_add_last(env, add);
		else
			symbol_add_alphabetic(env, add);
	}
}
