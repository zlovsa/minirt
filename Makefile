# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcarolee <mcarolee@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/07 19:13:40 by mcarolee          #+#    #+#              #
#    Updated: 2021/02/01 23:23:35 by mcarolee         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= minirt.c \
			vectors1.c \
			vectors2.c \
			intersect1.c \
			intersect2.c \
			parse1.c \
			parse2.c \
			parse3.c \
			savebmp.c \
			ray.c \
			light1.c \
			light2.c \
			util1.c \
			util2.c

OBJS	= $(SRCS:.c=.o)

NAME	= minirt

CC		= gcc
RM		= rm -f

CFLAGS	= -Wall -Wextra -Werror -lm

LFTDIR = ./libft/

LFT = $(LIBFTDIR)libft.a

all:		$(NAME)

$(NAME):	$(OBJS) $(LFT)
			$(CC) -g -fsanitize=address -o $(NAME) $(OBJS) -lm -L$(LFTDIR) -lft

$(LFT):
			make -C $(LFTDIR)

clean:
			$(RM) $(OBJS)
			make clean -C $(LFTDIR)

fclean:		clean
			$(RM) $(NAME)
			make fclean -C $(LFTDIR)
			
re:			fclean all

.PHONY:		all clean fclean re