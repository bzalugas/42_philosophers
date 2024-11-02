#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/10 12:55:15 by bazaluga          #+#    #+#              #
#    Updated: 2024/09/10 13:01:18 by bazaluga         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME	    :=	philo

SRCDIR	    :=	src

OBJDIR	    :=	obj

INCDIR	    :=	include

LIBFTDIR    :=	$(INCDIR)/libft

LIBFT	    :=	$(LIBFTDIR)/libft.a

SRC			:=

MAIN		:=	main.c

OBJ			:=  $(SRC:.c=.o)

OBJMAIN		:=	$(MAIN:.c=.o)

SRC	    	:=  $(addprefix $(SRCDIR)/, $(SRC))

OBJ	    	:=  $(addprefix $(OBJDIR)/, $(OBJ))

OBJMAIN    	:=  $(addprefix $(OBJDIR)/, $(OBJMAIN))

CC	    	:=  cc

CFLAGS	    :=  -Wall -Wextra -Werror -I$(INCDIR) -g3

LIBFLAGS	:=	-L$(LIBFTDIR)

########### COLORS ##########

RED		:=  "\033[1;31m"
GREEN	:=  "\033[1;32m"
RESET	:=  "\033[0m"

all:		$(NAME)

bonus:		$(NAME)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o:	$(SRCDIR)/%.c Makefile | $(OBJDIR)
	@printf $(GREEN)
	$(CC) $(CFLAGS) -MMD -c $< -o $@
	@printf $(RESET)

$(LIBFT):
	@echo $(GREEN)"\tCOMPILING LIBFT"$(RESET)
	@make -sC $(LIBFTDIR)
	@echo $(GREEN)"\tLIBFT COMPILED"$(RESET)

$(NAME):	$(LIBFT) $(OBJ) $(OBJMAIN)
	@echo $(GREEN)"LINKING mandatory objects to create <$(NAME)>"
	$(CC) $(OBJ) $(OBJMAIN) $(LIBFLAGS) -lft -o $(NAME)
	@echo "<$(NAME)> Created ✅"$(RESET)

libft:		$(LIBFT)
	@make -sC $(LIBFTDIR)

clean:
	@echo $(RED)"CLEANING OBJS"$(RESET)
	@rm -rf $(OBJDIR)

fclean:		clean
	@echo $(RED)"CLEANING ALL"$(RESET)
	@rm -f $(NAME)
	@rm -rf *.dSYM
	@make -sC $(LIBFTDIR) fclean

re:		fclean
	@make -s all

-include	$(OBJ:.o=.d)

.PHONY:		all clean fclean re bonus libft
