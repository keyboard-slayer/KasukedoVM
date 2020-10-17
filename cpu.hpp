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

#include <cstdint>
#include <array>
#include <cstddef>

class CPU
{
    private:
        std::array<int64_t, 8> _registers = {0};
        bool branch = 0;

    public:
        uint64_t pc = 0;

        void load_register(size_t, int64_t);
        int64_t get_value(size_t);
        void debug(void);
};

#endif