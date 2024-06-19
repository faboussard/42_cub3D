cmake_minimum_required(VERSION 3.27)
project(cub3d C)

set(CMAKE_C_STANDARD 11)

include_directories(includes)
include_directories(libft/inc)
include_directories(mlx_linux)

add_executable(cub3d
        headers/cub3d.h
        src/main.c
        libft/inc/get_next_line.h
        libft/inc/libft.h
        libft/src/ft_is/ft_isalnum.c
        libft/src/ft_is/ft_isalpha.c
        libft/src/ft_is/ft_isascii.c
        libft/src/ft_is/ft_isdigit.c
        libft/src/ft_is/ft_isprint.c
        libft/src/ft_lst/ft_lstadd_back.c
        libft/src/ft_lst/ft_lstadd_front.c
        libft/src/ft_lst/ft_lstclear.c
        libft/src/ft_lst/ft_lstdelone.c
        libft/src/ft_lst/ft_lstiter.c
        libft/src/ft_lst/ft_lstlast.c
        libft/src/ft_lst/ft_lstmap.c
        libft/src/ft_lst/ft_lstnew.c
        libft/src/ft_lst/ft_lstsize.c
        libft/src/ft_mem/ft_bzero.c
        libft/src/ft_mem/ft_calloc.c
        libft/src/ft_mem/ft_memchr.c
        libft/src/ft_mem/ft_memcmp.c
        libft/src/ft_mem/ft_memcpy.c
        libft/src/ft_mem/ft_memmove.c
        libft/src/ft_mem/ft_memset.c
        libft/src/ft_mem/ft_realloc.c
        libft/src/ft_printf/ft_printf.c
        libft/src/ft_printf/numbers_functions.c
        libft/src/ft_printf/strings_functions.c
        libft/src/ft_put/ft_putchar_fd.c
        libft/src/ft_put/ft_putendl_fd.c
        libft/src/ft_put/ft_putnbr_fd.c
        libft/src/ft_put/ft_putstr_fd.c
        libft/src/ft_str/ft_split.c
        libft/src/ft_str/ft_strchr.c
        libft/src/ft_str/ft_strcmp.c
        libft/src/ft_str/ft_strdup.c
        libft/src/ft_str/ft_striteri.c
        libft/src/ft_str/ft_strjoin.c
        libft/src/ft_str/ft_strlcat.c
        libft/src/ft_str/ft_strlcpy.c
        libft/src/ft_str/ft_strlen.c
        libft/src/ft_str/ft_strmapi.c
        libft/src/ft_str/ft_strncmp.c
        libft/src/ft_str/ft_strnstr.c
        libft/src/ft_str/ft_strrchr.c
        libft/src/ft_str/ft_strtrim.c
        libft/src/ft_str/ft_substr.c
        libft/src/ft_to/ft_atoi.c
        libft/src/ft_to/ft_atol.c
        libft/src/ft_to/ft_itoa.c
        libft/src/ft_to/ft_tolower.c
        libft/src/ft_to/ft_toupper.c
        libft/src/gnl/get_next_line.c
        libft/src/gnl/get_next_line_utils.c
        libft/src/utils.c
        mlx_linux/mlx.h
        mlx_linux/mlx_clear_window.c
        mlx_linux/mlx_destroy_display.c
        mlx_linux/mlx_destroy_image.c
        mlx_linux/mlx_destroy_window.c
        mlx_linux/mlx_expose_hook.c
        mlx_linux/mlx_ext_randr.c
        mlx_linux/mlx_flush_event.c
        mlx_linux/mlx_get_color_value.c
        mlx_linux/mlx_get_data_addr.c
        mlx_linux/mlx_hook.c
        mlx_linux/mlx_init.c
        mlx_linux/mlx_int.h
        mlx_linux/mlx_int_anti_resize_win.c
        mlx_linux/mlx_int_do_nothing.c
        mlx_linux/mlx_int_get_visual.c
        mlx_linux/mlx_int_param_event.c
        mlx_linux/mlx_int_set_win_event_mask.c
        mlx_linux/mlx_int_str_to_wordtab.c
        mlx_linux/mlx_int_wait_first_expose.c
        mlx_linux/mlx_key_hook.c
        mlx_linux/mlx_loop.c
        mlx_linux/mlx_loop_hook.c
        mlx_linux/mlx_mouse.c
        mlx_linux/mlx_mouse_hook.c
        mlx_linux/mlx_new_image.c
        mlx_linux/mlx_new_window.c
        mlx_linux/mlx_pixel_put.c
        mlx_linux/mlx_put_image_to_window.c
        mlx_linux/mlx_rgb.c
        mlx_linux/mlx_screen_size.c
        mlx_linux/mlx_set_font.c
        mlx_linux/mlx_string_put.c
        mlx_linux/mlx_xpm.c)

target_link_libraries(cub3d m)
target_link_libraries(cub3d X11)
target_link_libraries(cub3d Xrandr)
target_link_libraries(cub3d Xext)
