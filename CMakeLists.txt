cmake_minimum_required(VERSION 3.9.6)
project(Corewar C)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "-Wall -Werror -Wall -o2")

file(GLOB_RECURSE LIBFT
        libft/ft_printf/srcs/*.c
        libft/libft/srcs/*.c
        )

file(GLOB_RECURSE COREWAR
        srcs/VM/*.c
        )

include_directories(includes libft/libft/includes/ libft/ft_printf/includes/)
add_executable(corewar ${COREWAR} ${LIBFT})