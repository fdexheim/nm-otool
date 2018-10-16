/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 08:43:11 by fdexheim          #+#    #+#             */
/*   Updated: 2018/10/11 10:10:39 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OTOOL_H
# define OTOOL_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdbool.h>
# include <sys/stat.h>
# include <sys/mman.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach-o/fat.h>

# include <mach-o/ranlib.h>
# include <ar.h>

typedef struct				s_flag
{
	bool					file_opened;
	bool					fstat_sucess;
	bool					ptr_mmaped;
	bool					file_check_sucessful;
	bool					rightcputype_found;
	bool					rightcpusubtype_found;
}							t_flag;

typedef struct				s_obj_ctrl
{
	void					*obj_hdr;
	uint32_t				m_num;
	size_t					obj_offset;
	size_t					obj_size;
}							t_obj_ctrl;

typedef struct				s_env
{
	int						argc;
	char					**argv;
	t_flag					flags;
	char					*target;
	int						fd;
	struct stat				file_stats;
	char					*path;
	char					*ptr;
	char					*ptr_start;
	size_t					file_size;
	struct symtab_command	*symtab_cmd;
	void					*syms_start;
}							t_env;

bool						full_check_file(t_env *env);

bool						check_arch_64(t_env *env, t_obj_ctrl fat_ctrl,
		struct fat_header *fathdr);
bool						check_arch_32(t_env *env, t_obj_ctrl fat_ctrl,
		struct fat_header *fathdr);

bool						check_cmds(t_obj_ctrl macho_ctrl,
		struct load_command *cmds_start, const uint32_t ncmds);

bool						check_fat_64(t_env *env, t_obj_ctrl fat_ctrl);
bool						check_fat_32(t_env *env, t_obj_ctrl fat_ctrl);

bool						check_lc_seg_tab_32(struct mach_header *hdr,
		struct load_command *cmds_start, t_obj_ctrl macho_ctrl);
bool						check_lc_seg_tab_64(struct mach_header_64 *hdr64,
		struct load_command *cmds_start, t_obj_ctrl macho_ctrl);

bool						check_lctab_32(struct mach_header *hdr,
		struct load_command *cmds_start, t_obj_ctrl macho_ctrl);
bool						check_lctab_64(struct mach_header_64 *hdr64,
		struct load_command *cmds_start, t_obj_ctrl macho_ctrl);

bool						check_macho_64(t_env *env, t_obj_ctrl macho_ctrl);
bool						check_macho_32(t_env *env, t_obj_ctrl macho_ctrl);

bool						check_ar(t_env *env, t_obj_ctrl slib_ctrl);

bool						check_ar_objects(t_env *env,
		struct ar_hdr *obj_hdr);

bool						check_symtab(t_env *env, t_obj_ctrl macho_ctrl);

void						otool_display_32(t_obj_ctrl macho_ctrl,
		struct section *sect);
void						otool_display_64(t_obj_ctrl macho_ctrl,
		struct section_64 *sect64);

uint16_t					pui16(const uint16_t src, const uint32_t m_num);
uint32_t					pui32(const uint32_t src, const uint32_t m_num);
uint64_t					pui64(const uint64_t src, const uint32_t m_num);

struct section_64			*get_section_from_number_64(t_obj_ctrl macho_ctrl,
		const uint8_t num);
struct section				*get_section_from_number(t_obj_ctrl macho_ctrl,
		const uint8_t num);

void						*get_text_section_header(t_obj_ctrl macho_ctrl,
		struct load_command *cmds_start, const uint32_t ncmds);
struct load_command			*get_cmds(t_obj_ctrl macho_ctrl,
		struct load_command *cmds_start, const uint32_t cmd,
		const uint32_t size);

void						otool_handle_magic_number(t_env *env);

void						handle_arch_loop_64(t_env *env, t_obj_ctrl fat_ctrl,
		struct fat_header *fathdr);
void						handle_arch_loop_32(t_env *env, t_obj_ctrl fat_ctrl,
		struct fat_header *fathdr);

void						otool_handle_fat_32(t_env *env,
		t_obj_ctrl fat_ctrl);
void						otool_handle_fat_64(t_env *env,
		t_obj_ctrl fat_ctrl);

void						otool_handle_macho_32(t_obj_ctrl macho_ctrl);
void						otool_handle_macho_64(t_obj_ctrl macho_ctrl);

int							get_ar_name_size(struct ar_hdr *hdr);
bool						check_no_ranlib_duplicates(
		struct ranlib *ranlib_start, struct ranlib *ranlb);
bool						check_no_ranlib_duplicates_64(
		struct ranlib_64 *ranlib_start, struct ranlib_64 *ranlb);

void						otool_handle_ar(t_env *env, t_obj_ctrl ar_ctrl);

void						handle_ar_32_sorted(t_env *env, t_obj_ctrl ar_ctrl,
		struct ar_hdr *fhdr);
void						handle_ar_64_sorted(t_env *env, t_obj_ctrl ar_ctrl,
		struct ar_hdr *fhdr);

void						handle_ar_object(t_env *env,
		struct ar_hdr *obj_hdr);

int							otool(t_env *env);

bool						is_file(const char *argv);

void						print_full_number_64(const uint64_t src);
void						print_full_number_32(const uint32_t src);

void						debug_env(t_env *env);
void						free_env(t_env *env);
void						clean_exit(t_env *env);

struct mach_header_64		*get_mach_header_64(t_obj_ctrl macho_ctrl);
struct mach_header			*get_mach_header(t_obj_ctrl macho_ctrl);
bool						infile(t_env *env, size_t offest);
bool						inmacho(t_obj_ctrl macho_ctrl,
		const size_t offset_inmacho);
bool						is_64(const uint32_t magic_number);

void						open_file(t_env *env);
void						fstat_file(t_env *env);
void						mmap_ptr(t_env *env);
void						close_file(t_env *env);
void						munmap_ptr(t_env *env);

void						putnbr_bits_ghetto(size_t src, const uint8_t bits);
void						put_size_t_ghetto(const size_t src);
void						put_size_t_ghetto_hex(const size_t src);
void						put_unsigned_char_ghetto_hex(const unsigned char c);

int							atoi_ghetto(const char *str);

char						lowercase_ghetto(const char c);
int							strncmp_ghetto(const char *s1, const char *s2,
		const size_t size);
int							strcmp_ghetto(const char *s1, const char *s2);
size_t						strlen_ghetto(const char *s1);

void						putchar_ghetto(const char c);
void						putstr_ghetto(const char *str);
void						putstr_endl_ghetto(const char *str);

#endif
