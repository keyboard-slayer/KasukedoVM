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

#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

#include "parser.hpp"
#include "cpu.hpp"

bool 
valid_register(std::string reg)
{
    int id = reg[1] - '0';
    return reg[0] == 'r' && id > -1 && id < 10;
}

bool 
isnumber(const std::string& arg)
{
    return !arg.empty() && std::all_of(arg.begin(), arg.end(), ::isdigit);
}

int
load(std::vector<std::string> args, CPU *cpu)
{
    if (args.size() != 2 || !valid_register(args[0]))
    {
        return 1;
    }

    int64_t to_load;
    
    if (valid_register(args[1]))
    {
        to_load = cpu->get_value(args[1][1] - '0');
    }
    else if(isnumber(args[1]))
    {
        std::istringstream iss(args[1]);
        iss >> to_load;
    }
    else 
    {
        return 1;
    }

    cpu->load_register(args[0][1] - '0', to_load);

    return 0;
}

int 
math(std::vector<std::string> args, CPU *cpu, std::string operation)
{
    if (args.size() != 2 || !valid_register(args[0]))
    {
        return 1;
    }

    int64_t r = cpu->get_value(args[0][1] - '0');
    int64_t to_do;
    int64_t result;

    if (valid_register(args[1]))
    {
        to_do = cpu->get_value(args[1][1] - '0');
    }
    else if (isnumber(args[1]))
    {
        std::istringstream iss(args[1]);
        iss >> to_do;
    }
    else 
    {
        return 1;
    }

    if (operation == "ADD")
    {
        result = r + to_do;
    }

    if(operation == "SUB")
    {
        result = r - to_do;
    }

    if(operation == "MUL")
    {
        result = r * to_do;
    }

    if(operation == "DIV")
    {
        result = r / to_do;
    }

    cpu->load_register(args[0][1] - '0', result);
    return 0;
}

std::vector<std::string>
parse_args(std::string args)
{
    /* Maybe there's a more C++y way to do that */

    std::string tmp;
    std::vector<std::string> return_value;

    for (size_t i = 0; i < args.size(); i++)
    {
        if (args[i] == ',')
        {
            return_value.push_back(tmp);
            tmp.clear();
        } 
        else 
        {
            tmp += args[i];
        }
    }

    return_value.push_back(tmp);

    return return_value;
}

int 
parse(std::vector<std::string> code)
{
    int return_value = 1;
    std::vector<std::string> args;
    std::string mnemonic;
    pfunc func;
    CPU cpu;

    std::vector<std::string> mathfunc = {
        "ADD",
        "DIV",
        "MUL",
        "SUB"
    };

    std::map<std::string, pfunc> otherfunc
    {
        {"LOAD", load}
    };

    for (size_t i = 0; i < code.size(); i++)
    {
        if (code[i].rfind("//", 0) == 0 || code[i].length() == 0)
        {
            continue;  
        }

        mnemonic = code[i].substr(0, code[i].find(' '));
        transform(mnemonic.begin(), mnemonic.end(), mnemonic.begin(), ::toupper);

        code[i].erase(0, mnemonic.size()+1);
        code[i].erase(remove_if(code[i].begin(), code[i].end(), ::isspace), code[i].end());
        args = parse_args(code[i]);

        if (std::find(mathfunc.begin(), mathfunc.end(), mnemonic) != mathfunc.end())
        {
            return_value = math(args, &cpu, mnemonic);
        } 

        else 
        {
            func = otherfunc[mnemonic];
            return_value = func(args, &cpu);
        }

        if (return_value == 1)
        {
            fprintf(stderr, "\033[31mError\033[0m on line %ld\n", i+1);
            return 1;
        }

        cpu.pc += 1;
    }

    cpu.debug();

    return 0;
}