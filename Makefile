
# ---- Variables ---- #

NAME			=	cub3D

OS				=	$(shell uname)

RMF				=	rm -rf

# ---- Libraries ---- #

DIR_LIB			=	libft/
DIR_LIB_HEADER	=	libft/inc/

LIB				=	$(DIR_LIB)libft.a

DIR_MLX			=	mlx

# ---- Directories  ---- #

DIR_HEADERS     =   headers/

HEADERS			= 	$(DIR_HEADERS)cub3D.h \
					$(DIR_LIB_HEADER)libft.h

DIR_SRC	=	src/

SOURCES		=	$(DIR_SRC)main.c\
                $(DIR_SRC)raycasting.c\
                $(DIR_SRC)init.c\
                $(DIR_SRC)utils.c\
                $(DIR_SRC)hook.c\
                $(DIR_SRC)errors.c\
                $(DIR_SRC)exit.c\
                $(DIR_SRC)render.c\
                $(DIR_SRC)parsing.c\
                $(DIR_SRC)map.c\
                $(DIR_SRC)map_init.c\
                $(DIR_SRC)move.c

DIR_OBJS	    =	.objs/

# ---- Flags ---- #

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -Wno-deprecated-declarations
INCLUDES	=	-I $(DIR_LIB_HEADER) -I $(DIR_MLX) -I $(DIR_HEADERS)

# ---- MLX ---- #

MLX_FLAGS		=	-L $(DIR_MLX) -lm -lmlx -lX11 -lXext

# ---- Directory  objs ---- #

OBJS		=	$(addprefix $(DIR_OBJS),$(SOURCES:.c=.o))

# ====================== RULES ====================== #

# ---- Compilation rules ---- #

all:		${NAME}

${NAME}:	$(LIB) ${OBJS}
			make -C $(DIR_MLX)
			$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIB) $(MLX_FLAGS) -o $(NAME)

$(DIR_OBJS)%.o: %.c	$(HEADERS)
			@ mkdir -p ${dir $@}
			$(CC) $(CFLAGS) -c $< -o $@ -I $(DIR_HEADERS)

# ---- Library rule ---- #

$(LIB) :	FORCE
			$(MAKE) -C $(DIR_MLX)
			$(MAKE) -C $(DIR_LIB)

# ---- Clean rules ---- #

re :		fclean 
			$(MAKE) all
clean:
		$(MAKE) -C $(DIR_LIB) clean
		$(MAKE) -C $(DIR_MLX) clean
		$(RMF) $(DIR_OBJS)

fclean:		clean
		$(MAKE) -C $(DIR_LIB) fclean
		$(RMF) $(NAME)

debug:
		$(RMF) $(DIR_OBJS)
		$(MAKE) -C $(DIR_MLX)
		$(MAKE) CFLAGS="-g3"

fsan:
		$(RMF) $(DIR_OBJS)
		$(MAKE) -C $(DIR_MLX)
		$(MAKE) CFLAGS="-fsanitize=address"
		$(RMF) $(DIR_OBJS)


# ---- Phony ---- #
.PHONY :	all lib clean fclean re debug fsan FORCE
