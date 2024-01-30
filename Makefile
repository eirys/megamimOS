# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: etran <etran@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/30 15:41:37 by etran             #+#    #+#              #
#    Updated: 2024/01/30 17:52:18 by etran            ###   ########.fr        #
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

CXX			:=	gcc #c++
CFLAGS		:=	-fno-builtin \
				-fno-exceptions \
				-fno-stack-protector \
				-fno-rtti \
				-nostdlib \
				-nodefaultlibs \
				-m32

LD			:=	ld
LD_SCRIPT	:=	megamimOS.ld
LFLAGS		:=	-T$(LD_SCRIPT)

RM			:=	rm -rf

.PHONY: all
all: $(NAME)

$(NAME): $(OBJ_CPP) $(OBJ_ASM) $(LD_SCRIPT)
	@echo "Linking file $(NAME)..."
	@$(LD) $(LFLAGS) $(OBJ_CPP) $(OBJ_ASM) -o $(NAME)

.cpp.o:
	@echo "Compiling file $<..."
	@$(CXX) $(CFLAGS) -c $< -o $@

.s.o:
	@echo "Compiling file $<..."
	@$(ASM) $(ASFLAGS) $< -o $@

.PHONY: run
run: $(NAME)
	qemu-system-i386 -kernel megamimOS

#TODO
.PHONY: run-grub
run-grub: $(NAME)
	mkdir -p isodir/boot/grub
	cp $(NAME) isodir/boot/megamimOS
	cp grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -o megamimOS.iso isodir
	qemu-system-i386 -cdrom megamimOS.iso

.PHONY: clean
clean:
	@echo "Removing CPP objects."
	@$(RM) $(OBJ_CPP)
	@echo "Removing ASM objects."
	@$(RM) $(OBJ_ASM)

.PHONY: re
re: clean all