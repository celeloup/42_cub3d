# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: celeloup <celeloup@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/02 11:01:29 by celeloup          #+#    #+#              #
#    Updated: 2020/05/03 12:32:31 by celeloup         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= Cub3D
NAME_BONUS		= TheLegendOf_

SRCS_FILE		= cub3d.c \
				parsing.c \
				events.c \
				move.c \
				utils.c \
				structures_constructor.c \
				structures_destructor.c \
				structures_set.c \
				settings_set.c \
				sprite_set.c \
				sprite_render.c \
				raycasting.c \
				ray_shooting.c

SRCS_FILE_BONUS = cub3d_bonus.c \
				parsing_bonus.c \
				events_bonus.c \
				move_bonus.c \
				utils_bonus.c \
				structures_constructor_bonus.c \
				structures_destructor_bonus.c \
				structures_set_bonus.c \
				settings_set_bonus.c \
				sprite_set_bonus.c \
				sprite_render_bonus.c \
				raycasting_bonus.c \
				ray_shooting_bonus.c \
				minimap_bonus.c
				#print_debug_bonus.c

SRCS			= $(addprefix $(SRCS_DIR), $(SRCS_FILE))
OBJS			= $(addprefix $(OBJS_DIR), $(SRCS_FILE:.c=.o))

SRCS_BONUS		= $(addprefix $(SRCS_DIR_BONUS), $(SRCS_FILE_BONUS))
OBJS_BONUS		= $(addprefix $(OBJS_DIR_BONUS), $(SRCS_FILE_BONUS:.c=.o))
SRCS_DIR_BONUS	= ./bonus/srcs_bonus/
OBJS_DIR_BONUS	= ./bonus/objs_bonus/
INCLUDES_DIR_BONUS = ./bonus/includes_bonus/
INCLUDES_BONUS	= $(addprefix -I, $(INCLUDES_DIR_BONUS) $(LIBFT_DIR) $(LIBVECT_DIR) $(MLX_DIR))
HEADER_BONUS	= $(INCLUDES_DIR_BONUS)cub3d_bonus.h

SRCS_DIR		= ./srcs/
OBJS_DIR		= ./objs/
INCLUDES_DIR	= ./includes/
LIBFT_DIR		= ./lib/libft/
MLX_DIR			= ./lib/minilibx-linux/

LIBFT			= $(LIBFT_DIR)libft.a
MINILIBX		= $(MLX_DIR)libmlx.a
HEADER			= $(INCLUDES_DIR)cub3d.h

MLXFLAGS		= -lm -lXext -lX11 -lbsd
CFLAGS			= -Wall -Wextra -Werror -O2 -g#3 -fsanitize=address,undefined -Wpadded
CC				= clang

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

.PHONY: all launch clean fclean re norme title bonus
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
	$(MAKE) -sC $(LIBFT_DIR)
	echo

$(MINILIBX): FORCE
	$(MAKE) -sC $(MLX_DIR) 2>/dev/null

FORCE:

$(NAME): $(OBJS_DIR) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLXFLAGS) $(MINILIBX) -o $(NAME)

$(OBJS): $(OBJS_DIR)%.o: $(SRCS_DIR)%.c $(HEADER)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	printf $<

clean:
	$(MAKE) -sC $(LIBFT_DIR) clean
	$(MAKE) -sC $(MLX_DIR) clean
	$(RM) -r $(OBJS_DIR)

fclean: clean
	$(RM) $(LIBFT)
	$(RM) $(NAME)

re:
	$(MAKE) -s fclean
	$(MAKE) -s

norme:
	echo "Cube3D"
	norminette $(SRCS) $(HEADER)
	echo
	echo "LIBFT"
	$(MAKE) -C $(LIBFT_DIR) norme
	echo
	
bonus:
	echo "BONUS"
	$(MAKE) $(LIBFT)
	$(MAKE) $(MINILIBX)
	echo $(_CLEAR)$(_YELLOW)"building - "$(_GREEN)$(NAME_BONUS)$(_END)
	$(MAKE) $(NAME_BONUS)
	echo $(_GREEN)"\nDone. Have a fun time playing :)"$(_END)$(_SHOW_CURS)

$(NAME_BONUS): $(OBJS_DIR_BONUS) $(OBJS_BONUS)
	$(CC) $(CFLAGS) $(OBJS_BONUS) $(LIBFT) $(MLXFLAGS) $(MINILIBX) -o $(NAME_BONUS)

$(OBJS_DIR_BONUS):
	mkdir $@

$(OBJS_BONUS): $(OBJS_DIR_BONUS)%.o: $(SRCS_DIR_BONUS)%.c $(HEADER_BONUS)
	$(CC) $(CFLAGS) $(INCLUDES_BONUS) -c $< -o $@
	printf $<

bonus_clean:
	$(MAKE) -sC $(LIBFT_DIR) clean
	$(MAKE) -sC $(MLX_DIR) clean
	$(RM) -r $(OBJS_DIR_BONUS)

bonus_fclean: bonus_clean
	$(RM) $(LIBFT)
	$(RM) $(NAME_BONUS)