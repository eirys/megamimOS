# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: etran <etran@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/08 14:44:58 by etran             #+#    #+#              #
#    Updated: 2024/02/08 15:45:29 by etran            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ---------------------------------------------- #
#                     TARGETS                    #
# ---------------------------------------------- #

# ------------------ LIB NAME ------------------ #
NAME		:=	libmegamim.a

# --------------- DIRECTORY NAMES -------------- #
SRC_DIR		:=	src
OBJ_DIR		:=	obj

SRC_FILES	:=	strlen.cpp
OBJ_FILES	:=	$(SRC_FILES:.cpp=.o)

SRC			:=	$(addprefix $(SRC_DIR)/,$(SRC_FILES))
OBJ			:=	$(addprefix $(OBJ_DIR)/,$(SRC_FILES:.cpp=.o))
DEP			:=	$(addprefix $(OBJ_DIR)/,$(SRC_FILES:.cpp=.d))

# ----------------- COMPILATION ---------------- #
CXX			:=	c++
CFLAGS		:=	-Wall \
				-Wextra \
				-Werror \
				-MMD \
				-MP \
				-std=c++20 \
				-O3 \
				-m32

ARCHIVER	:=	ar
ARFLAGS		:=	rcs

# -------------------- MISC -------------------- #
RM			:=	rm -rf

# ---------------------------------------------- #
#                      RULES                     #
# ---------------------------------------------- #

.PHONY: all
all: $(NAME)

-include $(DEP)

# Compile library
$(NAME): $(OBJ)
	@echo "Compiling $(NAME)..."
	@$(ARCHIVER) $(ARFLAGS) $(NAME) $(OBJ)
	@echo "\`$(NAME)\` successfully created."

# Compile obj files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	@echo "Compiling file $<..."
	@$(CXX) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	@${RM} $(OBJ_DIR)
	@echo "Cleaned object files."

.PHONY: fclean
fclean: clean
	@${RM} $(NAME)
	@echo "Removed $(NAME)."

.PHONY: re
re: fclean all