/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 12:43:30 by fdexheim          #+#    #+#             */
/*   Updated: 2018/10/11 12:40:50 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_H
# define NM_H
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

typedef struct				s_symbol
{
	struct s_symbol			*next;
	uint64_t				index;
	bool					bad_index;
	char					effective_letter;
	char					*name;
	uint32_t				n_strx;
	uint8_t					n_type;
	uint8_t					n_sect;
	uint16_t				n_desc;
	uint64_t				n_value;
}							t_symbol;

typedef struct				s_flag
{
	bool					r;
	bool					p;
	bool					j;
	bool					u;
	bool					uppercase_u;
	bool					file_opened;
	bool					fstat_sucess;
	bool					ptr_mmaped;
	bool					file_check_sucessful;
	bool					right_cputype_found;
	int						nbfiles;
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
	t_symbol				*symbol_list;
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

char						calc_effective_letter(t_obj_ctrl macho_ctrl,
		t_symbol *sym);

bool						full_check_file(t_env *env);

bool						check_ar(t_env *env,
		t_obj_ctrl statlib_ctrl);

bool						check_arch_64(t_env *env, t_obj_ctrl fat_ctrl,
		struct fat_header *fathdr);
bool						check_arch_32(t_env *env, t_obj_ctrl fat_ctrl,
		struct fat_header *fathdr);

bool						check_fat_64(t_env *env, t_obj_ctrl ctrl);
bool						check_fat_32(t_env *env, t_obj_ctrl ctrl);

bool						check_lc_seg_tab_64(struct mach_header_64 *hdr64,
		struct load_command *cmds_start, t_obj_ctrl macho_ctrl);
bool						check_lc_seg_tab_32(struct mach_header *hdr,
		struct load_command *cmds_start, t_obj_ctrl macho_ctrl);

bool						check_lctab_64(struct mach_header_64 *hdr64,
		struct load_command *cmds_start, t_obj_ctrl macho_ctrl);
bool						check_lctab_32(struct mach_header *hdr,
		struct load_command *cmds_start, t_obj_ctrl macho_ctrl);

bool						check_macho_32(t_env *env, t_obj_ctrl ctrl);
bool						check_macho_64(t_env *env, t_obj_ctrl ctrl);

bool						check_symtab(t_env *env, t_obj_ctrl macho_ctrl);

bool						check_ar_objects(t_env *env,
		struct ar_hdr *obj_hdr);

void						display(t_env *env, t_obj_ctrl macho_ctrl);

uint16_t					pui16(const uint16_t src,
		const uint32_t magic_number);
uint32_t					pui32(const uint32_t src,
		const uint32_t magic_number);
uint64_t					pui64(const uint64_t src,
		const uint32_t magic_number);

struct section				*get_section_from_number(t_obj_ctrl macho_ctrl,
		const uint8_t num);
struct section_64			*get_section_from_number_64(t_obj_ctrl macho_ctrl,
		const uint8_t num);

struct load_command			*get_cmds(t_obj_ctrl macho_ctrl,
		struct load_command *cmds_start,
		const uint32_t cmd, const uint32_t size);

void						nm_handle_magic_number(t_env *env);

void						nm_handle_ar(t_env *env, t_obj_ctrl statlib_ctrl);

void						handle_ar_object(t_env *env,
		struct ar_hdr *objhdr);

void						handle_ar_32_sorted(t_env *env, t_obj_ctrl ar_ctrl,
		struct ar_hdr *fhdr);
void						handle_ar_64_sorted(t_env *env, t_obj_ctrl ar_ctrl,
		struct ar_hdr *fhdr);

int							get_ar_name_size(struct ar_hdr *hdr);
bool						check_no_ranlib_duplicates(
		struct ranlib *ranlb_start, struct ranlib *ranlb_cmp);
bool						check_no_ranlib_duplicates_64(
		struct ranlib_64 *ranlb_start, struct ranlib_64 *ranlb_cmp);

void						handle_arch_loop_32(t_env *env, t_obj_ctrl fat_ctrl,
		struct fat_header *fat_hdr);
void						handle_arch_loop_64(t_env *env, t_obj_ctrl fat_ctrl,
		struct fat_header *fat_hdr);

void						nm_handle_fat_64(t_env *env,
		t_obj_ctrl fat_ctrl);
void						nm_handle_fat_32(t_env *env,
		t_obj_ctrl fat_ctrl);

void						nm_handle_macho_32(t_env *env,
		t_obj_ctrl macho_ctrl);
void						nm_handle_macho_64(t_env *env,
		t_obj_ctrl macho_ctrl);

void						handle_symtab(t_env *env, t_obj_ctrl macho_ctrl);

int							nm(t_env *env);

bool						is_file(const char *argv);
void						parse_nm_args(t_env *env);

void						print_full_number_64(const uint64_t src);
void						print_full_number_32(const uint32_t src);

void						full_free_symbol_list(t_env *env);
void						symbol_add_first(t_env *env, t_symbol *add);
void						symbol_add_last(t_env *env, t_symbol *add);
t_symbol					*get_symbol_from_list_index(t_symbol *start,
		const size_t index);
size_t						get_symbol_list_size(t_symbol *start);

void						symbol_add(t_env *env, t_symbol *add);

int							smbcmp_value(const t_symbol *s1,
		const t_symbol *s2);
int							smbcmp_name(const t_symbol *s1, const t_symbol *s2);
int							smbcmp_strx(const t_symbol *s1, const t_symbol *s2);
int							smbcmp_namestrx(const t_symbol *s1,
		const t_symbol *s2);

void						debug_env(t_env *env);
void						free_env(t_env *env);
void						clean_exit(t_env *env);

struct mach_header			*get_mach_header(t_obj_ctrl macho_ctrl);
struct mach_header_64		*get_mach_header_64(t_obj_ctrl macho_ctrl);
bool						infile(t_env *env, const size_t offset);
bool						inmacho(t_obj_ctrl macho_ctrl,
		const size_t offset_inmacho);
bool						is_64(uint32_t magic_number);

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
		size_t size);
int							strcmp_ghetto(const char *s1, const char *s2);
size_t						strlen_ghetto(const char *str);

void						putchar_ghetto(const char c);
void						putstr_ghetto(const char *str);
void						putstr_endl_ghetto(const char *str);

#endif
