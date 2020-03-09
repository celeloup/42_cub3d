# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: celeloup <celeloup@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/02 11:01:29 by celeloup          #+#    #+#              #
#    Updated: 2020/03/09 14:05:25 by celeloup         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= Cub3D

SRCS1			= cub3d.c parsing.c events.c utils.c

SRCS			= $(addprefix $(SRCS_DIR), $(SRCS1))
OBJS			= $(addprefix $(OBJS_DIR), $(SRCS1:.c=.o))

SRCS_DIR		= ./srcs/
OBJS_DIR		= ./objs/
INCLUDES_DIR	= ./includes/
LIBFT_DIR		= ./libft/

LIBFT			= $(LIBFT_DIR)libft.a
MINILIBX		= $(MLX_DIR)libmlx.a
HEADER			= $(INCLUDES_DIR)cub3d.h

CFLAGS			= -Wall -Wextra -Werror -O2 -g #3 -fsanitize=address,undefined -Wpadded
CC				= clang

MLX_DIR		= ./minilibx/
INCLUDES	= $(addprefix -I, $(INCLUDES_DIR) $(LIBFT_DIR) $(LIBVECT_DIR) $(MLX_DIR))
FRAMEWORK	= -framework OpenGL -framework Appkit


##################
##    COLORS    ##
##################

_BLACK		= "\033[30m"
_RED		= "\033[31m"
_GREEN		= "\033[32m"
_YELLOW		= "\033[33m"
_BLUE		= "\033[34m"
_VIOLET		= "\033[35m"
_CYAN		= "\033[36m"
_WHITE		= "\033[37m"
_END		= "\033[0m"
_CLEAR		= "\033[2K"
_HIDE_CURS	= "\033[?25l"
_SHOW_CURS	= "\033[?25h"
_UP			= "\033[A"
_CUT		= "\033[k"

##################
##   TARGETS    ##
##################

.PHONY: all launch clean fclean re norme title
.SILENT:

all: launch

launch:
	$(MAKE) $(LIBFT)
	$(MAKE) $(MINILIBX)
	echo $(_CLEAR)$(_YELLOW)"building - "$(_GREEN)$(NAME)$(_END)
	$(MAKE) $(NAME)
	echo $(_GREEN)"\nDone."$(_END)$(_SHOW_CURS)

$(OBJS_DIR):
	mkdir $@

$(LIBFT): FORCE
	$(MAKE) -sC libft
	echo

$(MINILIBX): FORCE
	$(MAKE) -sC $(MLX_DIR) 2>/dev/null

FORCE:

$(NAME): $(OBJS_DIR) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(FRAMEWORK) $(MINILIBX) -o $(NAME)

$(OBJS): $(OBJS_DIR)%.o: $(SRCS_DIR)%.c $(HEADER)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	printf $<

clean:
	$(MAKE) -sC libft clean
	$(MAKE) -sC $(MLX_DIR) clean
	$(RM) -r $(OBJS_DIR)

fclean: clean
	$(MAKE) -sC libft fclean
	$(RM) $(NAME)

re:
	$(MAKE) -s fclean
	$(MAKE) -s

norme:
	echo "Cube3D"
	norminette $(SRCS) $(HEADER)
	echo
	echo "LIBFT"
	$(MAKE) -C libft norme
	echo