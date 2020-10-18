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

#ifndef _KASUKEDO_CPU_HPP_
#define _KASUKEDO_CPU_HPP_

#include <array>
#include <vector>
#include <string>
#include <map>

#include <cstdint>
#include <cstddef>

class CPU
{
    private:
        std::array<int64_t, 8> _registers = {0};
        std::map<std::string, std::vector<std::string>> _labelcode;
        std::map<std::string, int64_t> _label_position;

    public:
        uint64_t pc = 0;
        uint64_t ip = 0;
        uint64_t end = 0;
        uint8_t branch = false; /* 1 is eq, 2 is lt, 3 is gt */

        void load_register(size_t, int64_t);
        void add_code_label(std::string, std::string);
        void declare_label(std::string);
        void debug(void);

        int64_t get_value(size_t);
        int64_t get_label_ip(std::string);

        bool label_declared(std::string);

        std::vector<std::string> get_label_code(std::string);

};

#endif