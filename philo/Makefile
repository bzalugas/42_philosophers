#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/10 12:55:15 by bazaluga          #+#    #+#              #
#    Updated: 2024/11/08 12:40:48 by bazaluga         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME	    :=	philo

SRCDIR	    :=	src

OBJDIR	    :=	obj

INCDIR	    :=	include

SRC	    :=	ft_atoi.c \
		ft_putstr_fd.c \
		main_utils.c \
		monitoring.c \
		philo.c \
		philo_utils.c \
		printing.c \
		write_number.c

MAIN	    :=	main.c

OBJ	    :=  $(SRC:.c=.o)

OBJMAIN	    :=	$(MAIN:.c=.o)

SRC	    :=  $(addprefix $(SRCDIR)/, $(SRC))

OBJ	    :=  $(addprefix $(OBJDIR)/, $(OBJ))

OBJMAIN	    :=  $(addprefix $(OBJDIR)/, $(OBJMAIN))

CC	    :=  cc

CFLAGS	    :=  -Wall -Wextra -Werror -pthread -I$(INCDIR) -g3

########### COLORS ##########

RED	:=  "\033[1;31m"
GREEN	:=  "\033[1;32m"
RESET	:=  "\033[0m"

all:		$(NAME)

bonus:		$(NAME)

$(OBJDIR):
		@mkdir -p $(OBJDIR)

$(OBJDIR)/%.o:	$(SRCDIR)/%.c Makefile | $(OBJDIR)
		@printf $(GREEN)
		$(CC) $(CFLAGS) -MMD -c $< -o $@
		@printf $(RESET)

$(NAME):	$(OBJ) $(OBJMAIN)
		@echo $(GREEN)"\nLINKING mandatory objects to create <$(NAME)>"
		$(CC) $(OBJ) $(OBJMAIN) -o $(NAME)
		@echo "<$(NAME)> Created ✅"$(RESET)

clean:
		@echo $(RED)"CLEANING OBJS"$(RESET)
		@rm -rf $(OBJDIR)

fclean:		clean
		@echo $(RED)"CLEANING ALL"$(RESET)
		@rm -f $(NAME)
		@rm -rf *.dSYM

re:		fclean all

-include	$(OBJ:.o=.d) $(OBJMAIN:.o=.d)

.PHONY:		all clean fclean re bonus libft
