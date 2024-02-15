# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/30 15:41:37 by etran             #+#    #+#              #
#    Updated: 2024/02/15 14:52:47 by nmathieu         ###   ########.fr        #
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

CORE_DIR		:=	core
DRIVER_DIR		:=	drivers

UI_DIR			:=	ui
LAYOUT_DIR		:=	$(UI_DIR)/layout

CPU_DIR			:=	cpu
IDT_DIR			:=	$(CPU_DIR)/idt
GDT_DIR			:=	$(CPU_DIR)/gdt
LIB_DIR			:=	lib

# ---------------- SUB DIRECTORIES ------------- #
SUBDIRS			:=	. \
					$(CORE_DIR) \
					$(DRIVER_DIR) \
					$(UI_DIR) \
					$(LAYOUT_DIR) \
					$(GDT_DIR) \
					$(IDT_DIR) \
					$(CPU_DIR) \
					$(LIB_DIR)

OBJ_SUBDIRS		:=	$(addprefix $(OBJ_DIR)/,$(SUBDIRS))
INC_SUBDIRS		:=	$(addprefix $(SRC_DIR)/,$(SUBDIRS))

# ---------------- SOURCE FILES ---------------- #
SRC_FILES_CPP	:=	main.cpp \
					panic.cpp \
					$(CORE_DIR)/runtime.cpp \
					$(LAYOUT_DIR)/qwerty.cpp \
					$(UI_DIR)/terminal.cpp \
					$(UI_DIR)/window_manager.cpp \
					$(UI_DIR)/command_handler.cpp \
					$(DRIVER_DIR)/vga.cpp \
					$(DRIVER_DIR)/pic.cpp \
					$(DRIVER_DIR)/serial.cpp \
					$(DRIVER_DIR)/pit.cpp \
					$(GDT_DIR)/gdt.cpp \
					$(IDT_DIR)/pic_handler.cpp \
					$(IDT_DIR)/idt.cpp \
					$(IDT_DIR)/exception.cpp \
					$(LIB_DIR)/memcmp.cpp \
					$(LIB_DIR)/memcpy.cpp \
					$(LIB_DIR)/memset.cpp \
					$(LIB_DIR)/memmove.cpp \
					$(LIB_DIR)/strlen.cpp \
					$(LIB_DIR)/strcpy.cpp \
					$(LIB_DIR)/strcmp.cpp

SRC_FILES_ASM	:=	boot.s \
					$(GDT_DIR)/load_gdt.s \
					$(IDT_DIR)/load_idt.s

SRC_ASM			:=	$(addprefix $(SRC_DIR)/,$(SRC_FILES_ASM))
SRC_CPP			:=	$(addprefix $(SRC_DIR)/,$(SRC_FILES_CPP))

OBJ_ASM			:=	$(addprefix $(OBJ_DIR)/,$(SRC_FILES_ASM:.s=.o))
OBJ_CPP			:=	$(addprefix $(OBJ_DIR)/,$(SRC_FILES_CPP:.cpp=.o))
DEP				:=	$(addprefix $(OBJ_DIR)/,$(SRC_FILES_CPP:.cpp=.d))

# ----------------- COMPILATION ---------------- #
ASM				?=	nasm
ASFLAGS			:=	-felf32

CXX				?=	c++
MACROS			:=	KERNEL_NAME=\"$(NAME)\" \
					_DEBUG

CFLAGS			:=	-std=c++20 \
					-MMD \
					-MP \
					-Wall \
					-Wextra \
					-Werror \
					-fno-builtin \
					-fno-exceptions \
					-fno-stack-protector \
					-fno-rtti \
					-nostdlib \
					-nodefaultlibs \
					-mno-red-zone \
					-mgeneral-regs-only \
					-O3 \
					-m32

INCLUDES		:=	$(addprefix -I./,$(INC_SUBDIRS)) \
					-I$(LIB_DIR)
DEFINES			:=	$(addprefix -D,$(MACROS))

LD				?=  ld
LD_SCRIPT		:=	$(CONFIG_DIR)/megamimOS.ld
LD_LIBS			:=	$(LIB_DIR)/libmegamim.a

LFLAGS			:=	-T$(LD_SCRIPT)

GRUB_CFG		:=	grub.cfg
GRUB			:=	grub-mkrescue

QEMU			:=	qemu-system-i386
QEMU_FLAGS		:=	-serial stdio

# -------------------- MISC -------------------- #
RM				:=	rm -rf

# ---------------------------------------------- #
#                      RULES                     #
# ---------------------------------------------- #

.PHONY: all
all: $(LD_LIBS) $(NAME)

-include $(DEP)

$(LD_LIBS):
	@$(MAKE) -s -C $(LIB_DIR)

# Compile kernel
$(NAME): $(OBJ_CPP) $(OBJ_ASM) $(LD_SCRIPT)
	@echo "Linking file $(NAME)..."
	@$(LD) $(LFLAGS) $(OBJ_CPP) $(OBJ_ASM) -o $(NAME) $(LD_LIBS)
	@echo "\`$(NAME)\` successfully created."

# Compile obj files (cpp)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR) $(OBJ_SUBDIRS)
	@echo "Compiling file $<..."
	@$(CXX) $(CFLAGS) $(INCLUDES) $(DEFINES) -c $< -o $@

# Compile obj files (asm)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.s
	@mkdir -p $(OBJ_DIR) $(OBJ_SUBDIRS)
	@echo "Compiling file $<..."
	@$(ASM) $(ASFLAGS) $< -o $@

.PHONY: run
run: all
	@$(QEMU) -kernel $(NAME) $(QEMU_FLAGS)

.PHONY: run-grub
run-grub: all
	@mkdir -p $(ISO_DIR)/boot/grub
	@cp $(NAME) $(ISO_DIR)/boot/$(NAME)
	@cp $(CONFIG_DIR)/$(GRUB_CFG) $(ISO_DIR)/boot/grub/$(GRUB_CFG)
	@echo "Creating $(ISO)..."
	@$(GRUB) -o $(ISO) $(ISO_DIR)
	@echo "Running $(ISO)..."
	@$(QEMU) -cdrom $(ISO) $(QEMU_FLAGS)

.PHONY: clean
clean:
	@echo "Removing $(NAME) objects."
	@$(RM) $(OBJ_DIR)
	@echo "Removing $(ISO)".
	@$(RM) $(ISO)

.PHONY: fclean
fclean: clean
	@$(MAKE) -s -C $(LIB_DIR) fclean
	@echo "Removing $(NAME)."
	@$(RM) $(NAME)
	@echo "Removing $(ISO_DIR)."
	@$(RM) $(ISO_DIR)

.PHONY: re
re: fclean all
