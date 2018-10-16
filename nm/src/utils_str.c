/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 13:49:44 by fdexheim          #+#    #+#             */
/*   Updated: 2018/09/24 14:12:37 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/nm.h"

char				lowercase_ghetto(const char c)
{
	if ((c <= 'Z') && (c >= 'A'))
		return (c + 32);
	return (c);
}

int					strncmp_ghetto(const char *s1, const char *s2, size_t size)
{
	size_t			i;

	i = 0;
	while ((s1[i] || s2[i]) && i < size)
	{
		if (s1[i] != s2[i])
			return (strcmp_ghetto(s1, s2));
		i++;
	}
	return (0);
}

int					strcmp_ghetto(const char *s1, const char *s2)
{
	size_t			i;

	i = 0;
	while (s1[i] == s2[i])
	{
		if (s1[i] == '\0' && s2[i] == '\0')
			return (0);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

size_t				strlen_ghetto(const char *str)
{
	size_t			ret;

	ret = 0;
	if (str == NULL)
		return (0);
	while (*str)
	{
		ret++;
		str++;
	}
	return (ret);
}
