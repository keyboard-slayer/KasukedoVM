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
isnumber(std::string arg)
{
    return !arg.empty() && std::all_of(arg.begin(), arg.end(), ::isdigit);
}

int 
jeq(std::vector<std::string> args, CPU *cpu)
{
    if (cpu->branch == 1)
    {
        return jmp(args, cpu);
    } 

    return 0;
}

int 
jneq(std::vector<std::string> args, CPU *cpu)
{
    if (cpu->branch != 1)
    {
        return jmp(args, cpu);
    }

    return 0;
}

int 
jlt(std::vector<std::string> args, CPU *cpu)
{
    if (cpu->branch == 2)
    {
        return jmp(args, cpu);
    }

    return 0;
}

int 
jgt(std::vector<std::string> args, CPU *cpu)
{
    if (cpu->branch == 3)
    {
        return jmp(args, cpu);
    }

    return 0;
}

int 
jmp(std::vector<std::string> args, CPU *cpu)
{
    int return_code;

    transform(args[0].begin(), args[0].end(), args[0].begin(), ::toupper);

    if (!cpu->label_declared(args[0]))
    {
        return 1;
    }

    cpu->ip = cpu->get_label_ip(args[0]);

    return_code = parse(cpu->get_label_code(args[0]), cpu);

    cpu->ip = cpu->end;
    return return_code;
}

int
load(std::vector<std::string> args, CPU *cpu)
{
    int64_t to_load;

    if (args.size() != 2 || !valid_register(args[0]))
    {
        return 1;
    }

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
out(std::vector<std::string> args, CPU *cpu)
{
    (void) args;
    cpu->debug();

    return 0;
}

int 
cmp(std::vector<std::string> args, CPU *cpu)
{
    int64_t val1;
    int64_t val2;

    if (args.size() != 2)
    {
        return 1;
    }

    if (valid_register(args[0]))
    {
        val1 = cpu->get_value(args[0][1] - '0');
    }
    else 
    {
        std::istringstream iss(args[0]);
        iss >> val1;
    }

    if (valid_register(args[1]))
    {
        val2 = cpu->get_value(args[1][1] - '0');
    } 
    else 
    {
        std::istringstream iss(args[1]);
        iss >> val2;
    }

    if (val1 == val2)
    {
        cpu->branch = 1;
    } 
    else if(val1 < val2)
    {
        cpu->branch = 2;
    }
    else if(val1 > val2)
    {
        cpu->branch = 3;
    }

    return 0;
}

int 
math(std::vector<std::string> args, CPU *cpu, std::string operation)
{
    int64_t to_do;
    int64_t result;
    int64_t r = cpu->get_value(args[0][1] - '0');

    if (args.size() != 2 || !valid_register(args[0]))
    {
        return 1;
    }

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
    else if (operation == "SUB")
    {
        result = r - to_do;
    }
    else if (operation == "MUL")
    {
        result = r * to_do;
    }
    else if (operation == "DIV")
    {
        result = r / to_do;
    }
    else if (operation == "OR")
    {
        result = r | to_do;
    }
    else if (operation == "AND")
    {
        result = r & to_do;
    }
    else if (operation == "XOR")
    {
        result = r ^ to_do;
    }
    else 
    {
        return 1;
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
    size_t i;

    for (i = 0; i < args.size(); i++)
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

std::string  
remove_align(std::string code)
{
    std::string result;
    size_t i;
    bool found_code = false;

    for(i = 0; i < code.length(); i++)
    {
        if (code[i] == ' ' && !found_code)
        {
            continue;
        }

        else 
        {
            found_code = true;
            result += code[i];
        }
    }

    return result;
}

int 
parse(std::vector<std::string> code, CPU *cpu)
{
    std::vector<std::string> args;
    std::string label_name;
    std::string mnemonic;
    pfunc func;

    int return_value = 1;
    std::vector<std::string> orginal_code = code;

    std::vector<std::string> mathfunc = {
        "ADD",
        "DIV",
        "MUL",
        "SUB",
        "AND",
        "OR",
        "XOR"
    };

    std::map<std::string, pfunc> otherfunc
    {
        {"LOAD", load},
        {"JMP", jmp},
        {"OUT", out},
        {"CMP", cmp}, 
        {"JEQ", jeq}
    };

    if (cpu->end == 0)
    {
        cpu->end = code.size();
    }
    
    for (cpu->ip = 0; cpu->ip < code.size(); cpu->ip++)
    {
        if (code[cpu->ip].rfind("//", 0) == 0 || code[cpu->ip].length() == 0)
        {
            continue;  
        }

        if (label_name.size() && code[cpu->ip][0] == ' ')
        {
            cpu->add_code_label(label_name, remove_align(code[cpu->ip]));
        }

        else 
        {
            label_name.clear();
            mnemonic = code[cpu->ip].substr(0, code[cpu->ip].find(' '));

            transform(mnemonic.begin(), mnemonic.end(), mnemonic.begin(), ::toupper);

            code[cpu->ip].erase(0, mnemonic.size()+1);
            code[cpu->ip].erase(remove_if(code[cpu->ip].begin(), code[cpu->ip].end(), ::isspace), code[cpu->ip].end());
            args = parse_args(code[cpu->ip]);

            if (std::find(mathfunc.begin(), mathfunc.end(), mnemonic) != mathfunc.end())
            {
                return_value = math(args, cpu, mnemonic);
            } 
            else if(mnemonic[mnemonic.length() -1] == ':')
            {
                label_name = mnemonic;
                label_name.pop_back();

                cpu->declare_label(label_name);
                return_value = 0;
            }
            else 
            {
                func = otherfunc[mnemonic];
                return_value = (*func)(args, cpu);
            }

            if (return_value == 1)
            {
                fprintf(stderr, "\033[31mError\033[0m on line %ld\n", cpu->ip+1);
                return 1;
            }
        }

        cpu->pc++;
    }

    return 0;
}