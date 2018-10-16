/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_full_number.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 14:51:17 by fdexheim          #+#    #+#             */
/*   Updated: 2018/10/04 09:48:11 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/otool.h"

static void			fill_zeroes_64(const uint64_t src)
{
	uint64_t		cmp;

	cmp = 0xFFFFFFFFFFFFFFF;
	while (cmp > src)
	{
		write(1, "0", 1);
		cmp /= 16;
	}
}

void				print_full_number_64(const uint64_t src)
{
	if (src == 0)
	{
		putstr_ghetto("0000000000000000");
	}
	else
	{
		fill_zeroes_64(src);
		put_size_t_ghetto_hex(src);
	}
}

static void			fill_zeroes_32(const uint32_t src)
{
	uint64_t		cmp;

	cmp = 0xFFFFFFF;
	while (cmp > src)
	{
		write(1, "0", 1);
		cmp /= 16;
	}
}

void				print_full_number_32(const uint32_t src)
{
	if (src == 0)
	{
		putstr_ghetto("00000000");
	}
	else
	{
		fill_zeroes_32(src);
		put_size_t_ghetto_hex(src);
	}
}
