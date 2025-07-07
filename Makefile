# ================================ SETTINGS ================================== #
NAME = miniRT

# compile and link
CC = cc
CFLAGS = -O3 -flto -Wall -Wextra -Werror -march=native -ffast-math -funroll-loops

# libft specifics
MLX_DIR		= ./lib/MLX42
MLX			= $(MLX_DIR)/build/libmlx42.a

LIBFTDIR	= lib/libft/
LIBFT		= $(LIBFTDIR)libft.a

# Includes for libft and libmath(s)
INCLUDES	= -I ./inc -I $(LIBFTDIR)inc
MLXLIB		= $(MLX_DIR)/build/libmlx42.a -ldl -lglfw -pthread -lm
LDFLAGS		= -L$(LIBFTDIR) -lft -lm
OBJ_DIR		= obj/
SRC_DIR		= src/

# ================================ SOURCES =================================== #

HEADERS		= inc/minirt.h \
				inc/linear_algebra.h \
				inc/parsing.h \
				inc/raytracing.h \
				inc/typedefs.h \
				inc/utils.h

SRCS		= src/main.c \
				src/colors/colors_ops.c \
				src/colors/colour_conversion.c \
				src/drawing/hooks.c \
				src/drawing/render.c \
				src/error/exit_error.c \
				src/init/init_camera.c \
				src/init/init_objects.c \
				src/init/init.c \
				src/init/obj_rotation.c \
				src/init/obj_transformation_matrix.c \
				src/intersections/computations.c \
				src/intersections/intersect_cylinder.c \
				src/intersections/intersect_utils.c \
				src/intersections/intersections.c \
				src/lighting/lighting.c \
				src/lighting/shadows.c \
				src/matrices_tuples/matrix_determinant.c \
				src/matrices_tuples/matrix_minor_sub.c \
				src/matrices_tuples/matrix_ops.c \
				src/matrices_tuples/matrix_ops2.c \
				src/matrices_tuples/matrix_transform_rotation.c \
				src/matrices_tuples/matrix_transform.c \
				src/matrices_tuples/tuples_create.c \
				src/matrices_tuples/tuples_ops.c \
				src/matrices_tuples/tuples_ops2.c \
				src/parse/file_operations.c \
				src/parse/parse_check_attributes_1.c \
				src/parse/parse_check_attributes_2.c \
				src/parse/parse_check_opt_obj.c \
				src/parse/parse_check_scene_obj.c \
				src/parse/parse_obj_list.c \
				src/parse/parse_obj_type.c \
				src/parse/parse_utils.c \
				src/parse/parsing.c \
				src/raytracing/normal.c \
				src/raytracing/rays.c \
				src/raytracing/shading.c \
				src/utils/ft_split_set.c \
				src/utils/is_equal.c \
				src/utils/utils_conversions.c \
				src/utils/utils_error.c \
				src/utils/utils_matrix.c

OBJS		= $(SRCS:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

# ================================ RULES ===================================== #
# $@ = target.
# $< = first prerequisite. $^ = all prerequisites $? = prereq newer than target
all : $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJS) $(HEADERS)
	$(CC) $(CFLAGS) $(OBJS) $(MLXLIB) $(INCLUDES) $(LDFLAGS) -o $@
	@echo "---- ==== miniRT success. ==== ----"

$(LIBFT):
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

clean:
	@make clean -C $(LIBFTDIR)
	rm -rf $(OBJ_DIR)

fclean: clean
	@make fclean -C $(LIBFTDIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re

# .PHONY tells make that the commands are not files.
# Make doesn't worry about whether they are actual files or not. It will always
#     run these unless other targets are present and up-to-date.
