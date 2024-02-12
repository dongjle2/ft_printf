SRCS_MAND := fmt_s_bonus.c fmt_u_bonus.c fmt_x_bonus.c fmt_c_bonus.c fmt_p_bonus.c fmt_d.c ft_printf_helper.c ft_numtoa.c ft_printf_bonus_copy.c
OBJS_MAND := $(SRCS_MAND:.c=.o)
# SRCS_BONUS := ft_printf_bonus.c ft_numtoa.c ft_printf_helper.c \
# ./fmt_d/{both_precision_width.c ft_printf_d_bonus.c}
# OBJS_BONUS=$(SRCS_BONUS:.c=.o)

LIBFT_DIR := ./libft
DEP_ARC := libft.a

CFLAGS := -g -fsanitize=address

NAME := libftprintf.a

all: $(NAME)

$(DEP_ARC):
	make -C $(LIBFT_DIR) all
	cp $(LIBFT_DIR)/$(DEP_ARC) .

$(NAME): $(DEP_ARC) $(OBJS_MAND)
	mv $(DEP_ARC) $(NAME)
	ar rcs $(NAME) $(OBJS_MAND)

bonus: $(NAME)

clean:
	make -C $(LIBFT_DIR) fclean
	rm -f *.o

re: fclean all

fclean: clean
	rm -f $(NAME)