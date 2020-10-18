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


load r0, 1
load r1, 1 

// I want the 13th number of the fibonacci suite
load r2, 11

// The counter 
load r3, 0

main:
    cmp r3, r2 
    jeq end

    // r4 is the tmp value
    load r4, r0 
    
    load r0, r1 
    add r1, r4 

    add r3, 1
    jmp main

end:
    load r1, r0 
    xor r1, r1
    xor r2, r2 
    xor r3, r3 
    xor r4, r4
    out

jmp main