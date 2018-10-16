/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 08:49:27 by fdexheim          #+#    #+#             */
/*   Updated: 2018/10/11 12:43:01 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/nm.h"

static void		display_effective_symbol_letter(t_symbol *sym)
{
	write(1, " ", 1);
	write(1, &sym->effective_letter, 1);
	write(1, " ", 1);
}

static void		printerino_numberino(t_symbol *sym, t_obj_ctrl macho_ctrl)
{
	if (sym->effective_letter != 'U' || sym->bad_index == true)
	{
		if (is_64(macho_ctrl.m_num))
			print_full_number_64(sym->n_value);
		else
			print_full_number_32(sym->n_value);
	}
	else
	{
		if (is_64(macho_ctrl.m_num))
			putstr_ghetto("                ");
		else
			putstr_ghetto("        ");
	}
}

static void		display_symbol(t_env *env, t_symbol *sym, t_obj_ctrl macho_ctrl)
{
	if ((sym->effective_letter == 'U' || sym->effective_letter == 'u')
			&& env->flags.uppercase_u == true)
		return ;
	if (sym->effective_letter != 'U' && sym->effective_letter != 'u'
			&& env->flags.u == true)
		return ;
	if (env->flags.j == false)
	{
		printerino_numberino(sym, macho_ctrl);
		display_effective_symbol_letter(sym);
	}
	if (sym->n_strx == 0)
		putstr_ghetto("");
	else if (sym->bad_index == false)
		putstr_ghetto(sym->name);
	else if (sym->bad_index == true)
		putstr_ghetto("bad string index");
	putstr_ghetto("\n");
}

static void		display_reverse(t_env *env, t_obj_ctrl macho_ctrl)
{
	size_t		list_size;

	list_size = get_symbol_list_size(env->symbol_list);
	while (list_size > 0)
	{
		display_symbol(env,
				get_symbol_from_list_index(env->symbol_list, list_size),
				macho_ctrl);
		list_size--;
	}
}

void			display(t_env *env, t_obj_ctrl macho_ctrl)
{
	t_symbol	*sym;

	sym = env->symbol_list;
	if (env->flags.r == true)
		display_reverse(env, macho_ctrl);
	else
	{
		while (sym != NULL)
		{
			if (sym->effective_letter != '-')
				display_symbol(env, sym, macho_ctrl);
			sym = sym->next;
		}
	}
	full_free_symbol_list(env);
}
