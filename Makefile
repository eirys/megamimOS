# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: etran <etran@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/30 15:41:37 by etran             #+#    #+#              #
#    Updated: 2024/01/30 15:48:21 by etran            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:=	megamimOS

SRC_CPP	:=	$(shell find src/ -name '*.cpp')
SRC_ASM	:=	$(shell find src/ -name '*.s')

OBJ_CPP	:=	$(SRC_CPP:.cpp=.o)
OBJ_ASM	:=	$(SRC_ASM:.s=.o)



# ----------------- COMPILATION ---------------- #
ASM			:=	nasm
ASFLAGS		:=	-felf32

CXX			:=	c++
CFLAGS		:=	-fno-builtin \
				-fno-exceptions \
				-fno-stack-protector \
				-fno-rtti \
				-nostdlib \
				-nodefaultlibs \
				-m32

LD			:=	ld
LFLAGS		:=

RM			:=	rm -rf

.PHONY: all
all: $(NAME)

$(NAME): $(OBJ_CPP) $(OBJ_ASM)
	@echo "Linking file $(NAME)..."
	@$(LD) -TmegamimOS.ld $(LFLAGS) -o $(NAME) $(OBJ_CPP) $(OBJ_ASM)

.cpp.o:
	@echo "Compiling file $<..."
	@$(CXX) $(CFLAGS) -c $< -o $@

.s.o:
	@echo "Compiling file $<..."
	@$(ASM) $(ASFLAGS) $< -o $@

.PHONY: run
run: $(NAME)
	qemu-system-i386 -kernel $(NAME) --machine q35

.PHONY: clean
clean:
	@echo "Removing CPP objects."
	@$(RM) $(OBJ_CPP)
	@echo "Removing ASM objects."
	@$(RM) $(OBJ_ASM)

# .PHONY: fclean re # etc tmtc