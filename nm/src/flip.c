/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flip.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 13:21:18 by fdexheim          #+#    #+#             */
/*   Updated: 2018/10/02 15:35:05 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/nm.h"

uint16_t			pui16(const uint16_t src, const uint32_t m_num)
{
	uint16_t		ret;

	ret = 0;
	if (m_num == MH_MAGIC || m_num == MH_MAGIC_64
			|| m_num == FAT_MAGIC || m_num == FAT_MAGIC_64)
		return (src);
	ret = (src >> 8) | (src << 8);
	return (ret);
}

uint32_t			pui32(const uint32_t src, const uint32_t m_num)
{
	uint32_t		ret;

	ret = 0;
	if (m_num == MH_MAGIC || m_num == MH_MAGIC_64
			|| m_num == FAT_MAGIC || m_num == FAT_MAGIC_64)
		return (src);
	ret = ((src >> 24) & 0xff) | ((src << 8) & 0xff0000) | ((src >> 8) & 0xff00)
		| ((src << 24) & 0xff000000);
	return (ret);
}

uint64_t			pui64(const uint64_t src, const uint32_t m_num)
{
	uint64_t		ret;

	ret = src;
	if (m_num == MH_MAGIC || m_num == MH_MAGIC_64
			|| m_num == FAT_MAGIC || m_num == FAT_MAGIC_64)
		return (src);
	ret = ((ret << 8) & 0xFF00FF00FF00FF00ULL)
		| ((ret >> 8) & 0x00FF00FF00FF00FFULL);
	ret = ((ret << 16) & 0xFFFF0000FFFF0000ULL)
		| ((ret >> 16) & 0x0000FFFF0000FFFFULL);
	ret = (ret << 32) | (ret >> 32);
	return (ret);
}
