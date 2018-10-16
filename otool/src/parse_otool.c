/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_nm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 12:31:17 by fdexheim          #+#    #+#             */
/*   Updated: 2018/10/08 09:56:49 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/otool.h"

bool				is_file(const char *argv)
{
	int				fd;

	if ((fd = open(argv, O_RDONLY)) < 0)
	{
		return (false);
	}
	else
		close(fd);
	return (true);
}
