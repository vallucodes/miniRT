NAME		= miniRT
CC			= cc
CFLAGS		= -g -Wextra -Wall #-Werror

MLX_DIR		= ./lib/MLX42
MLX			= $(MLX_DIR)/build/libmlx42.a
LIBFT_DIR 	= ./lib/libft
LIBFT 		= $(LIBFT_DIR)/libft.a

OBJ_DIR		= obj/
SRC_DIR		= src/

INCLUDES	= -I ./inc -I $(LIBFT_DIR)/inc

LIBFTH		= $(LIBFT_DIR)/inc/libft.h
HEADERS		= inc/minirt.h inc/raytracing.h
MLXLIB		= $(MLX_DIR)/build/libmlx42.a -ldl -lglfw -pthread -lm

SRC			=	main.c \
				dev/printing_helpers.c \
				dev/projectile.c \
				dev/testing.c \
				drawing/background.c \
				drawing/draw_current.c \
				drawing/hooks.c \
				init/init.c \
				raytracing/colors.c \
				raytracing/math.c \
				raytracing/matrix_math.c \
				raytracing/matrix_operators.c \
				raytracing/objects.c \
				raytracing/rays.c \
				raytracing/tuples.c \
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




# ================================ SETTINGS ================================== #
NAME = minirt

# libft specifics
MLX_DIR		= ./lib/MLX42
MLX			= $(MLX_DIR)/build/libmlx42.a
LIBFTDIR	= lib/libft/
LIBFT		= $(LIBFTDIR)libft.a

# compile and link
CC = cc
CFLAGS = -g -Wall -Wextra #-Werror
# Includes for libft and libmath(s)
INCLUDES = -I ./inc -I $(LIBFTDIR)inc
LDFLAGS = -L$(LIBFTDIR) -lft -lm
OBJ_DIR = obj/

# ================================ SOURCES =================================== #
# Wildcards not permitted by norm, but nice and easy for testing
HEADERS		= $(wildcard inc/*.h)
MLXLIB		= $(MLX_DIR)/build/libmlx42.a -ldl -lglfw -pthread -lm
SRCS		= $(wildcard src/*.c) $(wildcard src/**/*.c)
OBJS		= $(SRCS:src/%.c=$(OBJDIR)%.o)

# ================================ RULES ===================================== #
# $@ = target.
# $< = first prerequisite. $^ = all prerequisites $? = prereq newer than target
.PHONY : all
all : $(NAME)

$(NAME) : $(LIBFT) $(MLX) $(OBJS) $(HEADERS)
	$(CC) $(CFLAGS) $(MLXLIB) $(SRCS) $(INCLUDES) $(LDFLAGS) -o $@
	@echo "---- ==== miniRT success. ==== ----"

$(LIBFT) :
	@echo "---- Building libft ----"
	@make --no-print-directory -C $(LIBFTDIR)
	@echo "----  libft built.  ----"

$(MLX): $(MLX_DIR)
	@cmake $(MLX_DIR) -B $(MLX_DIR)/build
	@make -C $(MLX_DIR)/build -j4

$(MLX_DIR):
	git clone https://github.com/codam-coding-college/MLX42.git $@;

$(OBJ_DIR)%.o : src/%.c $(HEADERS)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

.PHONY : clean
clean :
	@make clean -C $(LIBFTDIR)
	rm -rf $(OBJDIR)

.PHONY : fclean
fclean : clean
	@make fclean -C $(LIBFTDIR)
	rm -f $(NAME)

.PHONY : re
re: fclean all

# .PHONY tells make that the commands are not files.
# Make doesn't worry about whether they are actual files or not. It will always
#     run these unless other targets are present and up-to-date.
