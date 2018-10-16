/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 09:01:24 by fdexheim          #+#    #+#             */
/*   Updated: 2018/10/05 09:29:02 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/nm.h"

void			open_file(t_env *env)
{
	if ((env->fd = open(env->target, O_RDONLY)) < 0)
	{
		putstr_ghetto("[Error] : open unsucessful\n");
		env->flags.file_opened = false;
	}
	else
		env->flags.file_opened = true;
}

void			fstat_file(t_env *env)
{
	if (fstat(env->fd, &env->file_stats) < 0)
	{
		putstr_ghetto("[Error] : fstat unsucessful\n");
		env->flags.fstat_sucess = false;
	}
	else
		env->flags.fstat_sucess = true;
}

void			mmap_ptr(t_env *env)
{
	if (env->flags.ptr_mmaped == true)
	{
		putstr_ghetto("[Error] : ptr already mapped\n");
		return ;
	}
	if ((env->ptr_start = mmap(0, env->file_stats.st_size,
					PROT_READ, MAP_PRIVATE, env->fd, 0)) == MAP_FAILED)
	{
		putstr_ghetto("[Error] : mmap unsucessful\n");
		env->flags.ptr_mmaped = false;
	}
	else
	{
		env->flags.ptr_mmaped = true;
		env->ptr = env->ptr_start;
	}
}

void			close_file(t_env *env)
{
	if (env->flags.file_opened == false)
	{
		putstr_ghetto("[Warning] : attempt to close unopened file\n");
		return ;
	}
	env->fd = close(env->fd);
	if (env->fd < 0)
	{
		putstr_ghetto("[Error] : close unsucessful\n");
		env->flags.file_opened = true;
	}
	else
		env->flags.file_opened = false;
}

void			munmap_ptr(t_env *env)
{
	if (env->flags.ptr_mmaped == false)
	{
		putstr_ghetto("[Warning] : attempt to unmap un-maped memory\n");
		return ;
	}
	if (munmap(env->ptr_start, env->file_stats.st_size) < 0)
	{
		putstr_ghetto("[Error] : munmap unsucessful\n");
		env->flags.ptr_mmaped = true;
	}
	else
	{
		env->flags.ptr_mmaped = false;
		env->ptr = NULL;
		env->ptr_start = NULL;
	}
}
