/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbols_compare.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/22 12:34:44 by fdexheim          #+#    #+#             */
/*   Updated: 2018/09/24 11:05:34 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/nm.h"

int			smbcmp_namestrx(const t_symbol *s1, const t_symbol *s2)
{
	if (s1->n_strx + (size_t)s1->name > s2->n_strx + (size_t)s2->n_strx)
		return (1);
	else if (s1->n_strx + (size_t)s1->name < s2->n_strx + (size_t)s2->n_strx)
		return (-1);
	return (0);
}

int			smbcmp_value(const t_symbol *s1, const t_symbol *s2)
{
	if (s1->n_value > s2->n_value)
		return (1);
	else if (s1->n_value < s2->n_value)
		return (-1);
	return (0);
}

int			smbcmp_name(const t_symbol *s1, const t_symbol *s2)
{
	if (strcmp_ghetto(s1->name, s2->name) > 0)
		return (1);
	else if (strcmp_ghetto(s1->name, s2->name) < 0)
		return (-1);
	return (0);
}

int			smbcmp_strx(const t_symbol *s1, const t_symbol *s2)
{
	if (s1->n_strx > s2->n_strx)
		return (1);
	else if (s1->n_strx < s2->n_strx)
		return (-1);
	return (0);
}
