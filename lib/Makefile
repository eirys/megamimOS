# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/08 14:44:58 by etran             #+#    #+#              #
#    Updated: 2024/02/12 02:17:18 by jodufour         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ---------------------------------------------- #
#                     TARGETS                    #
# ---------------------------------------------- #

# ------------------ LIB NAME ------------------ #
NAME		:=	libmegamim.a
TEST		:=	test.out

# --------------- DIRECTORY NAMES -------------- #
SRC_DIR		:=	src
OBJ_DIR		:=	obj
INC_DIR		:=	include
TEST_DIR	:=	test

# ----------------- FILE NAMES ----------------- #
SRC			:=	\
	$(addsuffix .s, \
		strcmp \
		strcpy \
		strlen \
	)
OBJ			:=	$(addprefix $(OBJ_DIR)/,$(SRC:.s=.o))

TEST_SRC	:=	\
	$(addsuffix .cpp, \
		$(addprefix $(TEST_DIR)/, \
			main \
			strcmp \
			strcpy \
			strlen \
		) \
	)
TEST_OBJ	:=	$(addprefix $(OBJ_DIR)/,$(TEST_SRC:.cpp=.o))
TEST_DEP	:=	$(TEST_OBJ:.o=.d)

# ----------------- COMPILATION ---------------- #
AS			:=	$(shell which nasm)
ASFLAGS		:=	-felf32

CXX			:=	$(shell which c++)
CXXFLAGS	:=	-c \
				-Wall \
				-Wextra \
				-Wno-c++11-narrowing \
				-m32 \
				-fno-builtin \
				-MMD \
				-MP \
				-I$(INC_DIR)

# ------------------ LINKING ------------------- #
LINK		:=	$(shell which c++)
LFLAGS		:=	-m32

# -------------------- MISC -------------------- #
ARCHIVER	:=	$(shell which ar) rcs
RM			:=	$(shell which rm) -rf

# ---------------------------------------------- #
#                      RULES                     #
# ---------------------------------------------- #

.PHONY: all
all: $(NAME) $(TEST)

.PHONY: test
test: $(TEST)
# echo "Running unit tests..."
	./$(TEST)

# Create test binary
$(TEST): $(TEST_OBJ) $(NAME)
# echo "Linking unit tests..."
	$(LINK) $(LFLAGS) $^ $(OUTPUT_OPTION)
# echo "\`$(TEST)\` successfully created."

# Create library
$(NAME): $(OBJ)
# echo "Creating `$@`..."
	$(ARCHIVER) $@ $^
# echo "\`$@\` successfully created."

# Compile obj files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.s
	mkdir -p $(@D)
# echo "Compiling file $<..."
	$(AS) $(ASFLAGS) $< $(OUTPUT_OPTION)

-include $(TEST_DEP)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(@D)
# echo "Compiling file $<..."
	$(CXX) $(CXXFLAGS) $< $(OUTPUT_OPTION)


.PHONY: clean
clean:
	${RM} $(OBJ_DIR) $(NAME) $(TEST)
# echo "Removed object files and $(NAME)."

.PHONY: fclean
fclean: clean

.PHONY: re
re: clean all

.PHONY: fre
fre: fclean all
