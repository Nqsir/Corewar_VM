cmake_minimum_required(VERSION 3.9.6)
project(Corewar C)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "-Wall -Werror -Wall -o2")

file(GLOB_RECURSE LIBFT
        libft/libft/includes/*.h
        libft/ft_printf/includes/*.h
        libft/ft_printf/srcs/*.c
        libft/libft/srcs/*.c)

file(GLOB_RECURSE COREWAR
        srcs/VM/*.c
        includes/*.h)

include_directories(srcs)
include_directories(includes)
include_directories(libft/libft/includes)
include_directories(libft/libft/srcs)
include_directories(libft/ft_printf/includes)
include_directories(libft/ft_printf/srcs)

add_executable(corewar ${COREWAR} ${LIBFT})