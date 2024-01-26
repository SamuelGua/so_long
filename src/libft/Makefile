NAME = libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
AR = ar rcs
SRC = ft_isdigit.c ft_putchar_fd.c ft_strjoin.c ft_strtrim.c\
ft_isprint.c ft_putendl_fd.c ft_strlcat.c ft_substr.c ft_atoi.c\
ft_itoa.c ft_putnbr_fd.c ft_strlcpy.c ft_tolower.c ft_bzero.c\
ft_memchr.c ft_putstr_fd.c ft_strlen.c ft_toupper.c\
ft_calloc.c ft_memcmp.c ft_split.c ft_strmapi.c ft_isalnum.c ft_memcpy.c\
ft_strchr.c ft_strncmp.c ft_isalpha.c ft_memmove.c ft_strdup.c\
ft_strnstr.c ft_isascii.c ft_memset.c ft_striteri.c ft_strrchr.c\
get_next_line.c\


SRCB = $(wildcard *_bonus.c)
OBJ	= $(SRC:.c=.o)
OBJB = $(SRCB:.c=.o)



all : $(NAME)

bonus : $(OBJ) $(OBJB)
	$(AR) $(NAME) $(OBJ) $(OBJB)

%.o : %.c 
	$(CC) $(CFLAGS) -o $@  -c $<

$(NAME) : $(OBJ)
	$(AR) $(NAME) $(OBJ)

clean :
	$(RM) $(OBJ) $(OBJB)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : all bonus clean fclean re
