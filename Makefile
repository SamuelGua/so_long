COLOR_RESET = \033[0m
COLOR_RED = \033[91m
COLOR_GREEN = \033[92m
COLOR_YELLOW = \033[93m
COLOR_BOLD = \033[1m
MAKEFLAGS += --no-print-directory


NAME			:= so_long

SRC_DIR			:= src
OBJ_DIR			:= obj
SRCS			= $(PATH_LIBFT)  $(SO_LONG_PATH)
PATH_LIBFT		= $(libft:%=src/libft/%)
libft			= ft_isdigit.c ft_putchar_fd.c ft_strjoin.c ft_strtrim.c\
				ft_isprint.c ft_putendl_fd.c ft_strlcat.c ft_substr.c ft_atoi.c\
				ft_itoa.c ft_putnbr_fd.c ft_strlcpy.c ft_tolower.c ft_bzero.c\
				ft_memchr.c ft_putstr_fd.c ft_strlen.c ft_toupper.c ft_atol.c\
				ft_calloc.c ft_memcmp.c ft_split.c ft_strmapi.c ft_isalnum.c ft_memcpy.c\
				ft_strchr.c ft_strncmp.c ft_isalpha.c ft_memmove.c ft_strdup.c\
				ft_strnstr.c ft_isascii.c ft_memset.c ft_striteri.c ft_strrchr.c\
				ft_lstadd_back_bonus.c   ft_lstclear_bonus.c   ft_lstiter_bonus.c\
				ft_lstmap_bonus.c  ft_lstsize_bonus.c ft_lstadd_front_bonus.c  ft_lstdelone_bonus.c\
				ft_lstlast_bonus.c  ft_lstnew_bonus.c ft_free.c get_next_line.c\

SO_LONG_PATH	= $(so_long:%=src/so_long/%)
so_long		= parsing.c valid_way.c \
		
OBJS			:= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
CC = cc
#CFLAGS			:= -Wall -Wextra -Werror
CFLAGS			+= -g3
CCFLAGS			:= -I include

RM				:= rm -rf
DIR_DUP			= mkdir -p $(@D)

all: $(NAME)


$(NAME): $(OBJS)
		$(CC) $(OBJS) -o $(NAME) 
		@echo "$(COLOR_RED)$(COLOR_BOLD)Compilation fini  MAKEFILE INCOMPLET👍 $(COLOR_RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c include/libft.h include/so_long.h
		@$(DIR_DUP)
		$(CC) $(CFLAGS) $(CCFLAGS) -c -o $@ $<

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(OBJ_DIR) $(NAME)
	

re:
	@$(MAKE) fclean
	@$(MAKE) all


