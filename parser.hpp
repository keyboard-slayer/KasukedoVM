// Copyright (C) 2020 Jordan DALCQ & Contributors
// 
// This file is part of Kasukēdo.
// 
// Kasukēdo is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// Kasukēdo is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with Kasukēdo.  If not, see <http://www.gnu.org/licenses/>.

#ifndef _KASUKEDO_PARSER_HPP_
#define _KASUKEDO_PARSER_HPP_

#include "cpu.hpp"

typedef int (*pfunc)(std::vector<std::string>, CPU *);

int parse(std::vector<std::string>, CPU *);
int math(std::vector<std::string>, CPU *);

bool valid_register(std::string);
bool isnumber(std::string);

int jeq(std::vector<std::string>, CPU *);
int jneq(std::vector<std::string>, CPU *);
int jlt(std::vector<std::string>, CPU *);
int jgt(std::vector<std::string>, CPU *);
int jmp(std::vector<std::string>, CPU *);
int load(std::vector<std::string>, CPU *);
int out(std::vector<std::string>, CPU *);
int cmp(std::vector<std::string>, CPU *);

std::vector<std::string> parse_args(std::string);

std::string remove_align(std::string);

#endif