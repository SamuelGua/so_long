#!/bin/bash
cc -Wall -Wextra -Werror main.c  mlx/libmlx_Linux.a -L mlx -lXext -lX11 -lm -o so_long
valgrind ./so_long