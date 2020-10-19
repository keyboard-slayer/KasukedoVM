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


main:
    cmp r0, 0
    jeq end 

    push r0

    mod r0, 2 
    mul r0, r1 
    mul r1, 10

    add r3, r0
    pop r0
    div r0, 2
    jmp main

end:
    pop r0
    load r1, r3
    
    xor r2, r2
    xor r3, r3
    out
    
load r0, 69
push r0
load r1, 1
jmp main