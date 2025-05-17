NAME		= miniRT
CC			= cc
CFLAGS		= -Wextra -Wall -Werror

MLX_DIR		= ./lib/MLX42
MLX			= $(MLX_DIR)/build/libmlx42.a
LIBFT_DIR 	= ./lib/libft
LIBFT 		= $(LIBFT_DIR)/libft.a

OBJ_DIR		= obj/
SRC_DIR		= src/

INCLUDES	= -I ./inc -I $(LIBFT_DIR)/inc

LIBFTH		= $(LIBFT_DIR)/inc/libft.h
HEADERS		=	inc/minirt.h
MLXLIB		= $(MLX_DIR)/build/libmlx42.a -ldl -lglfw -pthread -lm

SRC			=	main.c \
				raytracing/colors.c \
				raytracing/tuples.c \
				raytracing/math.c \
				raytracing/matrices.c \
				raytracing/dev.c

OBJS		= $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

all: $(NAME)

$(LIBFT):
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR)

$(MLX): $(MLX_DIR)
	@cmake $(MLX_DIR) -B $(MLX_DIR)/build
	@make -C $(MLX_DIR)/build -j4

$(MLX_DIR):
	git clone https://github.com/codam-coding-college/MLX42.git $@;

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADERS)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -o $@ -c $< $(INCLUDES)

$(NAME): $(LIBFT) $(MLX) $(OBJS) $(HEADERS)
	@$(CC) $(OBJS) $(MLXLIB) $(LIBFT) -o $(NAME)
	@echo "\033[0;32mMiniRT built successfully ✅\033[0m"

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) clean
	@echo "\033[0;32mminiRT cleaned successfully ✅\033[0m"

fclean: clean
	@rm -f $(NAME) $(LIBFT)
	@rm -rf $(MLX_DIR)/build

re: fclean all

.PHONY: all, clean, fclean, re
