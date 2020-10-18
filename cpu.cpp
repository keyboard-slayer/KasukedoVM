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

#include "cpu.hpp"

#include <cstdio>

void CPU::load_register(size_t regid, int64_t value)
{
    this->_registers[regid] = value;
}

int64_t CPU::get_value(size_t regid)
{  
    return this->_registers[regid];
}

void CPU::add_code_label(std::string label, std::string code)
{
    _labelcode[label].push_back(code);
}

void CPU::declare_label(std::string label)
{
    _label_position[label] = this->ip;
}

bool CPU::label_declared(std::string label)
{
    return this->_labelcode.find(label)  != this->_labelcode.end();
}

int64_t CPU::get_label_ip(std::string label)
{
    return this->_label_position[label];
}

std::vector<std::string> CPU::get_label_code(std::string label)
{
    return this->_labelcode[label];
}

void CPU::debug(void)
{
    for(size_t i = 0; i < 8; i++)
    {
        if (i % 3 == 0 && i)
        {
            printf("\n");
        }

        printf("r%ld = %4ld\t", i, this->get_value(i));
    }

    printf("pc = %4ld\n", this->pc);
}