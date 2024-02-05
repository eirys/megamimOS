# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: etran <etran@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/30 15:41:37 by etran             #+#    #+#              #
#    Updated: 2024/02/05 16:43:12 by etran            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ---------------------------------------------- #
#                     TARGETS                    #
# ---------------------------------------------- #

# ------------------- KERNEL ------------------- #
NAME			:=	megamimOS
ISO				:=	$(NAME).iso

# --------------- DIRECTORY NAMES -------------- #
SRC_DIR			:=	src
OBJ_DIR			:=	obj
CONFIG_DIR		:=	config
ISO_DIR			:=	isodir

DRIVER_DIR		:=	drivers
WINDOW_DIR		:=	window

# ---------------- SUB DIRECTORIES ------------- #
SUBDIRS			:=	. \
					$(DRIVER_DIR) \
					$(WINDOW_DIR)

# OBJ_SUBDIRS	:=	$(addprefix $(OBJ_DIR)/,$(SUBDIRS))
INC_SUBDIRS		:=	$(addprefix $(SRC_DIR)/,$(SUBDIRS))

# ---------------- SOURCE FILES ---------------- #
SRC_FILES_CPP	:=	main.cpp
SRC_FILES_ASM	:=	entrypoint.s

SRC_ASM			:=	$(addprefix $(SRC_DIR)/,$(SRC_FILES_ASM))
SRC_CPP			:=	$(addprefix $(SRC_DIR)/,$(SRC_FILES_CPP))

OBJ_ASM			:=	$(addprefix $(OBJ_DIR)/,$(SRC_FILES_ASM:.s=.o))
OBJ_CPP			:=	$(addprefix $(OBJ_DIR)/,$(SRC_FILES_CPP:.cpp=.o))
DEP				:=	$(addprefix $(OBJ_DIR)/,$(SRC_FILES_CPP:.cpp=.d))

# ----------------- COMPILATION ---------------- #
ASM				:=	nasm
ASFLAGS			:=	-felf32

CXX				:=	c++
INCLUDES		:=	$(addprefix -I./,$(INC_SUBDIRS))
CFLAGS			:=	-std=c++20 \
					-MMD \
					-MP \
					-fno-builtin \
					-fno-exceptions \
					-fno-stack-protector \
					-fno-rtti \
					-nostdlib \
					-nodefaultlibs \
					-m32 \
					$(INCLUDES)

LD				:=	ld
LD_SCRIPT		:=	$(CONFIG_DIR)/megamimOS.ld
LFLAGS			:=	-T$(LD_SCRIPT)

GRUB_CFG		:=	grub.cfg
GRUB			:=	grub-mkrescue

# -------------------- MISC -------------------- #
RM				:=	rm -rf

# ---------------------------------------------- #
#                      RULES                     #
# ---------------------------------------------- #

.PHONY: all
all: $(NAME)

-include $(DEP)

# Compile kernel
$(NAME): $(OBJ_CPP) $(OBJ_ASM) $(LD_SCRIPT)
	@echo "Linking file $(NAME)..."
	@$(LD) $(LFLAGS) $(OBJ_CPP) $(OBJ_ASM) -o $(NAME)

# Compile obj files (cpp)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	@echo "Compiling file $<..."
	@$(CXX) $(CFLAGS) -c $< -o $@

# Compile obj files (asm)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.s
	@mkdir -p $(OBJ_DIR)
	@echo "Compiling file $<..."
	@$(ASM) $(ASFLAGS) $< -o $@

.PHONY: run
run: $(NAME)
	@qemu-system-i386 -kernel $(NAME)

.PHONY: run-grub
run-grub: $(NAME)
	mkdir -p $(ISO_DIR)/boot/grub
	cp $(NAME) $(ISO_DIR)/boot/$(NAME)
	cp $(GRUB_CFG)/$(GRUB_CFG) $(ISO_DIR)/boot/grub/$(GRUB_CFG)
	$(GRUB) -o $(ISO) $(ISO_DIR)
	qemu-system-i386 -cdrom $(ISO)

.PHONY: clean
clean:
	@echo "Removing objects."
	@$(RM) $(OBJ_DIR)
	@echo "Removing $(ISO)".
	@$(RM) $(ISO)

.PHONY: fclean
fclean: clean
	@echo "Removing $(NAME)."
	@$(RM) $(NAME)
	@echo "Removing $(ISO_DIR)."
	@$(RM) $(ISO_DIR)

.PHONY: re
re: fclean all