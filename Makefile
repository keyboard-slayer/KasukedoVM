# Copyright (C) 2020 Jordan DALCQ & Contributors
# 
# This file is part of Kasukēdo.
# 
# Kasukēdo is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# Kasukēdo is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with Kasukēdo.  If not, see <http://www.gnu.org/licenses/>.

CC := g++
CFLAGS :=      \
	-Wall      \
	-Wextra    \
	-I.		   \
	-std=c++20

src := $(wildcard *.cpp)

all:
	$(CC) $(CFLAGS) $(src) -o Kasukedo 
	
