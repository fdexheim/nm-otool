/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_nbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 09:51:31 by fdexheim          #+#    #+#             */
/*   Updated: 2018/10/02 15:56:07 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/nm.h"

void				putnbr_bits_ghetto(size_t src, const uint8_t bits)
{
	size_t			tmp;
	size_t			cmp;

	tmp = bits;
	cmp = 1;
	while (tmp > 1)
	{
		cmp = cmp * 2;
		tmp--;
	}
	tmp = bits;
	while (tmp > 0)
	{
		if (cmp <= src)
		{
			write(1, "1", 1);
			src -= cmp;
		}
		else
			write(1, "0", 1);
		cmp = cmp / 2;
		tmp--;
	}
}

void				put_size_t_ghetto(const size_t src)
{
	if (src >= 10)
		put_size_t_ghetto(src / 10);
	putchar_ghetto(src % 10 + '0');
}

void				put_size_t_ghetto_hex(const size_t src)
{
	const char		hexa[] = "0123456789abcdef";

	if (src >= 16)
		put_size_t_ghetto_hex(src / 16);
	putchar_ghetto(hexa[src % 16]);
}

void				put_unsigned_char_ghetto_hex(const unsigned char c)
{
	const char		hexa[] = "0123456789abcdef";

	if (c <= 0xf)
	{
		write(1, "0", 1);
		putchar_ghetto(hexa[c % 16]);
	}
	else
	{
		putchar_ghetto(hexa[c / 16]);
		putchar_ghetto(hexa[c % 16]);
	}
}
