/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   script.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 13:18:16 by fdexheim          #+#    #+#             */
/*   Updated: 2018/10/04 16:07:33 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <stdlib.h>
#include <iostream>

void				run(std::string arg)
{
	std::string		cmd;
	std::string		diffcmd;
	std::string		output;

	cmd = "./ft_otool " + arg + " > testosteronemine && otool -t " + arg + " > testosterone";
	diffcmd = "diff testosterone testosteronemine";

	std::cout << arg << " : " << std::endl;
	system(cmd.c_str());
	system(diffcmd.c_str());
}

int					main()
{
	run("a.out");
	run("ft_otool");
	run("../tests+/hell/32_exe_hard");
	run("../tests+/hell/64_bundle");
	run("../tests+/hell/64_exe_easy");
	run("../tests+/hell/64_exe_hard");
	run("../tests+/hell/64_exe_medium");
	run("../tests+/hell/64_exe_medium");
	run("../tests+/hell/64_lib_dynamic_hard");
	run("../tests+/hell/64_lib_dynamic_medium");
	run("../tests+/hell/PN548_API.dylib");
	run("../tests+/hell/PN548_HAL_OSX.dylib");
	run("../tests+/hell/PN548_OSX.dylib");
	run("../tests+/hell/appsleepd");
	run("../tests+/hell/bash");
	run("../tests+/hell/cfprefsd");
	run("../tests+/hell/distnoted");
	run("../tests+/hell/fat_hard");
	run("../tests+/hell/ft_nm32");
	run("../tests+/hell/libAccountPolicyTranslation.dylib");
	run("../tests+/hell/libFosl_dynamic.dylib");
	run("../tests+/hell/libftprintf.a");
	run("../tests+/hell/libftprintf32.a");
	run("../tests+/hell/libc++.1.dylib");
	run("../tests+/hell/ssh-keychain.dylib");
	run("../tests+/hell/sqlite3");
	run("../tests+/hell/libclapack.dylib");
	return 0;
}
