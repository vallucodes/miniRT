# ================================ SETTINGS ================================== #
NAME = minirt

# libft specifics
LIBFTDIR = lib/libft/
LIBFT = $(LIBFTDIR)libft.a

# compile and link 
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
# Includes for libft and libmath(s)
INCLUDES = -I ./src/inc -I $(LIBFTDIR)inc -L$(LIBFTDIR) -lft -lm
OBJDIR = obj/

# ================================ SOURCES =================================== #
# Wildcards not permitted by norm, but nice and easy for testing 
HEADERS = $(wildcard inc/*.h)
SRCS = $(wildcard src/*.c) $(wildcard src/parse/*.c) $(wildcard src/utils/*.c)
OBJS = $(SRCS:src/%.c=$(OBJDIR)%.o)

# ================================ RULES ===================================== #
# $@ = target.
# $< = first prerequisite. $^ = all prerequisites $? = prereq newer than target
.PHONY : all
all : $(NAME) 

$(NAME) : $(LIBFT) $(OBJS) $(HEADERS)
	$(CC) $(CFLAGS) $(SRCS) $(INCLUDES) -o $@
	@echo "---- ==== miniRT success. ==== ----"

$(LIBFT) :
	@echo "---- Building libft ----"
	@make --no-print-directory -C $(LIBFTDIR)
	@echo "----  libft built.  ----"

$(OBJDIR)%.o : src/%.c
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
