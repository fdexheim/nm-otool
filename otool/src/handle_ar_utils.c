/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_ar_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 13:39:06 by fdexheim          #+#    #+#             */
/*   Updated: 2018/10/04 15:50:07 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/otool.h"

int						get_ar_name_size(struct ar_hdr *hdr)
{
	char				*c;
	int					ret;

	c = hdr->ar_name;
	while (*c != '/')
		c++;
	c++;
	ret = atoi_ghetto(c);
	return (ret);
}

bool					check_no_ranlib_duplicates_64(
		struct ranlib_64 *ranlb_start, struct ranlib_64 *ranlb_cmp)
{
	struct ranlib_64	*ranlb;

	ranlb = ranlb_start;
	while (ranlb < ranlb_cmp)
	{
		if (ranlb->ran_off == ranlb_cmp->ran_off)
		{
			return (false);
		}
		ranlb++;
	}
	return (true);
}

bool					check_no_ranlib_duplicates(struct ranlib *ranlb_start,
		struct ranlib *ranlb_cmp)
{
	struct ranlib		*ranlb;

	ranlb = ranlb_start;
	while (ranlb < ranlb_cmp)
	{
		if (ranlb->ran_off == ranlb_cmp->ran_off)
		{
			return (false);
		}
		ranlb++;
	}
	return (true);
}
