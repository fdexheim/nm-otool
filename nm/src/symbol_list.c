/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 14:29:47 by fdexheim          #+#    #+#             */
/*   Updated: 2018/10/08 09:52:06 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/nm.h"

void			full_free_symbol_list(t_env *env)
{
	t_symbol	*tmp;
	t_symbol	*tmp2;

	tmp = env->symbol_list;
	while (tmp != NULL)
	{
		tmp2 = tmp;
		tmp = tmp->next;
		free(tmp2);
	}
	env->symbol_list = NULL;
}

void			symbol_add_first(t_env *env, t_symbol *add)
{
	add->next = env->symbol_list;
	env->symbol_list = add;
}

void			symbol_add_last(t_env *env, t_symbol *add)
{
	t_symbol	*sym;

	sym = env->symbol_list;
	while (sym->next != NULL)
	{
		sym = sym->next;
	}
	sym->next = add;
	add->next = NULL;
}

t_symbol		*get_symbol_from_list_index(t_symbol *start, const size_t index)
{
	size_t		cmp;
	t_symbol	*sym;

	cmp = 1;
	sym = start;
	while (cmp < index)
	{
		sym = sym->next;
		cmp++;
	}
	return (sym);
}

size_t			get_symbol_list_size(t_symbol *start)
{
	size_t		ret;
	t_symbol	*sym;

	ret = 0;
	sym = start;
	while (sym != NULL)
	{
		sym = sym->next;
		ret++;
	}
	return (ret);
}
