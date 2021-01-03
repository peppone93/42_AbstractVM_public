# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbianco <gbianco@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/21 23:17:10 by gbianco           #+#    #+#              #
#    Updated: 2020/12/22 02:16:16 by gbianco          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = avm

# COLOR------------------------
CLRR = \033[0;31m
CLRG = \033[0;32m
CLRB = \033[0;34m
CLRC = \033[0;36m
CLRW = \033[0m
AVM = $(CLRB)[AVM]$(CLRW)
#------------------------------

#MACOS -std=c++17
#SANITIZE -fsanitize=address
CLN++ = clang++ $(MACOS) $(SANITIZE)
FLAG = -Wall -Wextra -Werror

CPPF = main.cpp AbstractStack.cpp Exceptions.cpp Lexer.cpp OperandFactory.cpp \
		Parser.cpp

HPPF = AbstractStack.hpp Lexer.hpp Parser.hpp Exceptions.hpp Operand.hpp \
		main.hpp IOperand.hpp OperandFactory.hpp options.hpp

SRCD = ./srcs/
OBJD = ./compiled/
INCD = ./includes/

SRC = $(addprefix $(SRCD), $(CPPF))
OBJ = $(addprefix $(OBJD), $(CPPF:.cpp=.o))
INC = $(addprefix $(INCD), $(HPPF))

all: $(OBJD) $(NAME) 
	@printf	"$(AVM)Everything done\n"

$(OBJD):
	@printf	"$(AVM)%-50s [$(CLRR)%s$(CLRW)]" "Folder: $(OBJD) created" "✘"
	@mkdir compiled
	@printf	"\r$(AVM)%-50s [$(CLRG)%s$(CLRW)]\n" "Folder: $(OBJD) created" "✔"

# EXE--------------------------
$(NAME): $(OBJ)
	@printf	"$(AVM)%-50s [$(CLRR)%s$(CLRW)]" "$(NAME) compiled" "✘"
	@$(CLN++) $(FLAG) -o $@ $(OBJ)
	@printf	"\r$(AVM)$(CLRG)%-50s$(CLRW) [$(CLRG)%s$(CLRW)]\n" "$(NAME) compiled" "✔"
#------------------------------

# OBJECTS----------------------
$(OBJD)%.o: $(SRCD)%.cpp $(INC)
	@printf "$(AVM)%-50s [$(CLRR)%s$(CLRW)]" "Object $@ created" "✘"
	@$(CLN++) $(FLAG) -c $< -o $@ -I $(INCD)
	@printf "\r$(AVM)%-50s [$(CLRG)%s$(CLRW)]\n" "Object $@ created" "✔"
#------------------------------

clean:
	@rm -rf $(OBJD)
	@printf	"$(AVM)%-50s [$(CLRG)%s$(CLRW)]\n" "Folder: $(OBJD) removed" "∙"
fclean: clean
	@rm -rf $(NAME)
	@printf	"$(AVM)%-50s [$(CLRG)%s$(CLRW)]\n" "File: $(NAME) removed" "∙"

re: fclean all

.PHONY: all clean fclean re
