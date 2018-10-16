/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_str2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 09:14:47 by fdexheim          #+#    #+#             */
/*   Updated: 2018/09/24 09:15:39 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/nm.h"

void				putchar_ghetto(const char c)
{
	write(1, &c, 1);
}

void				putstr_ghetto(const char *str)
{
	if (str == NULL)
	{
		write(1, "(null)", 6);
		return ;
	}
	write(1, str, strlen_ghetto(str));
}

void				putstr_endl_ghetto(const char *str)
{
	write(1, str, strlen_ghetto(str));
	write(1, "\n", 1);
}
