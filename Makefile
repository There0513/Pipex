# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: threiss <threiss@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/26 15:54:56 by threiss           #+#    #+#              #
#    Updated: 2021/11/09 12:12:33 by threiss          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_PATH	=	./srcs/

B_SRCS_PATH	=	./bonus/

SRCS_NAMES	=	main.c \
				utils.c \
				utils_both.c \
				ft_split.c \
				exec.c \

B_SRCS_NAMES =	b_main.c \
				b_utils.c \
				../srcs/utils_both.c \
				../srcs/ft_split.c \
				../srcs/exec.c \
				get_next_line.c \

INCL	=	./includes/

NAME	= 	pipex

CC	=	clang

RM	=	rm -f

CFLAGS	=	-Wall -Wextra -Werror

SRCS	=	$(addprefix $(SRCS_PATH), $(SRCS_NAMES))

B_SRCS	=	$(addprefix $(B_SRCS_PATH), $(B_SRCS_NAMES))


OBJS	=	${SRCS:.c=.o}

B_OBJS	=	${B_SRCS:.c=.o}

.c.o:
		@${CC} ${CFLAGS} -I$(INCL) -c $< -o ${<:.c=.o} 

$(NAME):	${OBJS}
			${CC} ${CFLAGS} ${OBJS} -I${INCL} -o ${NAME}

all:		${NAME}

bonus:		${B_OBJS}
			${CC} ${CFLAGS} ${B_OBJS} -I${INCL} -o ${NAME}

clean:
		${RM} ${OBJS} ${B_OBJS}

fclean:		clean
		${RM} ${NAME}

re:		fclean all

.PHONY:
		all clean fclean re bonus
