# ================================ SETTINGS ================================== #
NAME = miniRT

# compile and link
CC = cc
CFLAGS = -g -O3 -flto -Wall -Wextra -march=native -ffast-math #-Werror
CFLAGS = -g -Wall -Wextra #-Werror

# libft specifics
MLX_DIR		= ./lib/MLX42
MLX			= $(MLX_DIR)/build/libmlx42.a
LIBFTDIR	= lib/libft/
LIBFT		= $(LIBFTDIR)libft.a

# Includes for libft and libmath(s)
INCLUDES = -I ./inc -I $(LIBFTDIR)inc
LDFLAGS = -L$(LIBFTDIR) -lft -lm
OBJ_DIR = obj/
SRC_DIR = src/

# ================================ SOURCES =================================== #
# Wildcards not permitted by norm, but nice and easy for testing
HEADERS		= $(wildcard inc/*.h)
MLXLIB		= $(MLX_DIR)/build/libmlx42.a -ldl -lglfw -pthread -lm
SRCS		= $(wildcard src/*.c) $(wildcard src/**/*.c)
OBJS		= $(SRCS:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

# ================================ RULES ===================================== #
# $@ = target.
# $< = first prerequisite. $^ = all prerequisites $? = prereq newer than target
all : $(NAME)

$(NAME) : $(LIBFT) $(MLX) $(OBJS) $(HEADERS)
	$(CC) $(CFLAGS) $(OBJS) $(MLXLIB) $(INCLUDES) $(LDFLAGS) -o $@
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

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADERS)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean :
	@make clean -C $(LIBFTDIR)
	rm -rf $(OBJ_DIR)

fclean : clean
	@make fclean -C $(LIBFTDIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re

# .PHONY tells make that the commands are not files.
# Make doesn't worry about whether they are actual files or not. It will always
#     run these unless other targets are present and up-to-date.
