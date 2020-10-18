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

#include <cstdio>
#include <fstream>
#include <iostream>
#include <vector>

#include "parser.hpp"
#include "cpu.hpp"

bool 
load_source(char *filename, std::vector<std::string> *code)
{
    std::ifstream source_file(filename);
    std::string line;

    if (!source_file.is_open())
    {
        return false;
    }

    while (getline(source_file, line))
    {
        code->push_back(line);
    }

    return true;
}

int 
main(int argc, char *argv[])
{
    std::vector<std::string> asm_code;
    CPU cpu;

    if (argc == 1)
    {
        fprintf(stderr, "\033[1m%s\033[0m: no file specified\n", argv[0]);
        return 1;
    }

    if (!load_source(argv[1], &asm_code))
    {
        fprintf(stderr, "\033[1m%s\033[0m: %s: No such file\n", argv[0], argv[1]);
        return 1;
    }

    return parse(asm_code, &cpu);
}