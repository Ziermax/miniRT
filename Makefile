#<-------------------------------|VARIABLES|---------------------------------->#

NAME		= miniRT
CC			= cc
CFLAGS		= -Wextra -Wall -Werror #-fsanitize=address
MLXFLAGS	= -ldl -lglfw -pthread -lm

#<-------------------------------|LIBRARIES|---------------------------------->#

MLX		= libmlx42.a
MLX_D	= ./MLX42/build/
LIBFT	= libft.a
LIBFT_D	= ./Libft/

#<---------------------------------|FILES|------------------------------------>#

SRC_D	= ./sources/
SRC_F	= main.c draw_scene.c \
		  struct_vector.c vector_operation.c vector_complex_op.c color.c \
		  ray_tracer.c intersections.c light_tracer.c object_normal.c

OBJ_D	= ./objects/
OBJ_F	= $(SRC_F:.c=.o)
OBJ 	= $(addprefix $(OBJ_D), $(OBJ_F))

DEP_D	= ./dependencies/
DEP_F	= $(SRC_F:.c=.d)
DEP		= $(addprefix $(DEP_D), $(DEP_F))

#<---------------------------------|RULES|------------------------------------>#

all: libmlx libft $(NAME)

libft:
	make -C $(LIBFT_D)

libmlx: $(MLX_D)
	cmake ./MLX42 -B $(MLX_D) && make -C $(MLX_D) -j4

$(OBJ_D)%.o: $(SRC_D)%.c Makefile
	$(CC) $(CFLAGS) -MMD -o $@ -c $<
	mv ${@:.o=.d} ${DEP_D}

$(NAME): $(DEP_D) $(OBJ_D) $(OBJ)
	$(CC) $(CFLAGS) $(MLXFLAGS) $(OBJ) $(MLX_D)$(MLX) $(LIBFT_D)$(LIBFT) -o $(NAME)

#<------------------------------|DIRECTORIES|--------------------------------->#

$(DEP_D):
	mkdir $(DEP_D)

$(OBJ_D):
	mkdir $(OBJ_D)

$(MLX_D):
	mkdir $(MLX_D)

#<---------------------------------|PHONY|------------------------------------>#

clean:
	rm -rf $(OBJ_D) $(DEP_D)

fclean: clean
	rm -rf $(MLX_D)
	make fclean -C $(LIBFT_D)
	rm -rf $(NAME)

re: clean all

-include $(DEP)

.PHONY: all clean fclean re libmlx
#<---------------------------------------------------------------------------->#
