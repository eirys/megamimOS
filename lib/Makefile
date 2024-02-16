# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/08 14:44:58 by etran             #+#    #+#              #
#    Updated: 2024/02/16 00:46:10 by jodufour         ###   ########.fr        #
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
		memcmp \
		memcpy \
		memset \
		memmov \
		strcmp \
		strcpy \
		strlen \
	)
OBJ			:=	$(addprefix $(OBJ_DIR)/,$(SRC:.s=.o))

TEST_SRC	:=	\
	$(addsuffix .cpp, \
		$(addprefix $(TEST_DIR)/, \
			tester \
			memcmp \
			memcpy \
			memmov \
			memset \
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
ifeq ($(DEBUG),1)
ASFLAGS		+=	-g
endif

CXX			:=	$(shell which c++)
CFLAGS		:=	-c \
				-Wall \
				-Wextra \
				-m32 \
				-fno-builtin \
				-MMD \
				-MP \
				-I$(INC_DIR)
ifeq ($(DEBUG),1)
CFLAGS		+=	-g \
				-fsanitize=address
endif

# ------------------ LINKING ------------------- #
LINK		:=	$(shell which c++)
LFLAGS		:=	-m32
ifeq ($(DEBUG),1)
LFLAGS		+=	-lasan
endif

# -------------------- MISC -------------------- #
ARCHIVER	:=	$(shell which ar) rcs
MKDIR		:=	$(shell which mkdir) -p
RM			:=	$(shell which rm) -rf

# ---------------------------------------------- #
#                      RULES                     #
# ---------------------------------------------- #

.PHONY: all
all: $(NAME)

.PHONY: test
test: $(TEST)
	@echo 'Running unit tests...'
	@./$(TEST)

# Create test binary
$(TEST): $(TEST_OBJ) $(NAME)
	@echo 'Linking unit tests into $(TEST)...'
	@$(LINK) $(LFLAGS) $^ $(OUTPUT_OPTION)
	@echo '$(TEST) successfully created.'

# Create library
$(NAME): $(OBJ)
	@echo 'Creating $@...'
	@$(ARCHIVER) $@ $^
	@echo '$@ successfully created.'

# Compile obj files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.s
	@$(MKDIR) $(@D)
	@echo 'Compiling file $<...'
	@$(AS) $(ASFLAGS) $< $(OUTPUT_OPTION)

-include $(TEST_DEP)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@$(MKDIR) $(@D)
	@echo "Compiling file $<..."
	@$(CXX) $(CFLAGS) $< $(OUTPUT_OPTION)


.PHONY: clean
clean:
	@echo 'Removing object files.'
	@$(RM) $(OBJ_DIR)

.PHONY: fclean
fclean: clean
	@echo 'Removing $(NAME).'
	@${RM} $(NAME)
	@echo 'Removing $(TEST).'
	@${RM} $(TEST)

.PHONY: re
re: fclean all
