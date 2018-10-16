/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_nbr2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 09:12:08 by fdexheim          #+#    #+#             */
/*   Updated: 2018/09/24 13:52:17 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/otool.h"

int					atoi_ghetto(const char *str)
{
	int				i;
	int				j;

	i = 0;
	j = 0;
	if (str[i] == '\033')
		return (0);
	while ((str[i] > 0 && str[i] <= 32) || str[i] == 127)
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (j != 0)
			j = j * 10;
		j += str[i] - '0';
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
		i--;
	if (str[i] == '-')
		return (-j);
	return (j);
}
