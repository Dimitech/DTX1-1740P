##############################################################################
#
# makefile for TMOS
#
# Copyright (C) 2008 Informa, www.informa-dev.com
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation.
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
# http://www.gnu.org/licenses/
#
##############################################################################
# Changelog:

################## Section 1. Variable definitions ###################

#=============== 1.A PROJECT Name ===============#
PROJECT_Name = DTX_1740P

#=============== 1.B PROJECT RELATED ===============#
# Project name used for the output files:
PROJECT = $(BIN_DIR)$(PROJECT_Name)
BIN_DIR := out/

# Output format. can be [ihex, binary]
FORMAT = ihex

# Debugging format.
#DEBUG = dwarf-2
DEBUG = gdb3

#  optimisation level  can be [0, 1, 2, 3, s].
OPT = -O0

#Linker script
LDSCRIPT = sam4s8b_flash.ld

# define location where to copy flash file
#ifdef COMSPEC
#	TFTP_PATH ?= \\tftpboot\\
#else
#	TFTP_PATH ?= /home/tftpboot/
#endif

#=============== 1.C HARDWARE SELECTION ===============#
MCU_ARCH = cortex-m4

#=============== 1.D global variables ===============#
# Initialize them here as simple variables.
modules 		:= apps cmsis_boot cmsis_core SAM4S_StdPeriph_Driver user_libs
prebuild 		:=
postbuild 		:=
asources 		:=
csources 		:=
libraries 		:=
cdefines 		:=
adefines 		:=
inc_dirs 		:= .
lib_dirs 		:=

aobjects = $(patsubst %.s,$(BIN_DIR)%.o,$(asources))
cobjects = $(patsubst %.c,$(BIN_DIR)%.o,$(csources))
sources = $(asources) $(csources)
objects = $(aobjects) $(cobjects)
listings = $(subst .o,.lst,$(objects))
dependencies = $(wildcard $(addsuffix .dep,$(objects)))

#=============== 1.E TOOLCHAIN COMMANDS ===============#
TOOLCHAIN_PREFIX 		= arm-none-eabi-
#TOOLCHAIN_PREFIX 		= arm-elf-
#TOOLCHAIN_PREFIX 		= 
CC 						= $(TOOLCHAIN_PREFIX)gcc
AS 						= $(TOOLCHAIN_PREFIX)as
LD 						= $(TOOLCHAIN_PREFIX)ld
CPP 					= $(TOOLCHAIN_PREFIX)g++
OBJCOPY 				= $(TOOLCHAIN_PREFIX)objcopy
OBJDUMP 				= $(TOOLCHAIN_PREFIX)objdump
NM 						= $(TOOLCHAIN_PREFIX)nm
SIZE 					= $(TOOLCHAIN_PREFIX)size
HEXSIZE 				= $(SIZE) --target=$(FORMAT) $(PROJECT).hex
ELFSIZE 				= $(SIZE) -A $(PROJECT).elf
REMOVE 					= rm -rf
REMOVEDIR 				= rm -rf

#=============== 1.F TOOLCHAIN FLAGS ===============#
# Flags for general use of gcc (asembling, compiling, linking)
GCCFLAGS += -mcpu=$(MCU_ARCH)
GCCFLAGS += -g$(DEBUG)
#GCCFLAGS += -g3
GCCFLAGS += -mthumb
GCCFLAGS += $(OPT) -fomit-frame-pointer -fverbose-asm
#GCCFLAGS += -ffunction-sections -fdata-sections
#GCCFLAGS += -DUSE_STDPERIPH_DRIVER -D__ASSEMBLY__ -Dgcc
#GCCFLAGS += -Dgcc
GCCFLAGS += -Dgcc

CFLAGS += $(addprefix -D,$(cdefines))
CFLAGS += $(addprefix -I,$(inc_dirs))
CFLAGS += -Wall 
#CFLAGS += -Wcast-align -Wimplicit
#CFLAGS += -Wstrict-prototypes
CFLAGS += -Wpointer-arith -Wswitch
#CFLAGS += -Wredundant-decls 
#CFLAGS += -Wshadow -Wunused
CFLAGS += -Wa,-adhlns=$(BIN_DIR)$(subst $(suffix $<),.lst,$<)

# flags only for C
CONLYFLAGS += -Wnested-externs -funsigned-char
CONLYFLAGS += -std=gnu99

# flags only for C++ (arm-elf-g++)
CPPFLAGS = -fno-rtti -fno-exceptions

# Assembler flags.
ASFLAGS += $(addprefix -D ,$(adefines))
ASFLAGS += $(addprefix -I,$(inc_dirs))

#AS -v 2.17> ASFLAGS += -Wa,-adhlns=--gen-debug,--gdwarf-2
ASFLAGS += -Wa,-adhlns=$(BIN_DIR)$(<:.s=.lst),--gstabs
ASFLAGS += -x assembler-with-cpp

# Compiler flags to generate dependency files.
GENDEPFLAGS = -MD -MP -MF $@.dep

# Linker flags.
#LDFLAGS += -nostartfiles -nostdlib
#LDFLAGS += -nostartfiles
LDFLAGS += -lc -lnosys -lm -lgcc
LDFLAGS += --specs=nosys.specs
#LDFLAGS += --specs=rdimon.specs
#LDFLAGS += -Wl,-Map=$(PROJECT).map,--cref,--gc-sections,--no-warn-mismatch
LDFLAGS += -Wl,-Map=$(PROJECT).map,--cref,--gc-sections
LDFLAGS += $(addprefix -L,$(lib_dirs))
LDFLAGS += -T$(LDSCRIPT)

########################### includes ############################################
# default goal is "all" - set it before include files
all:
# $(call changepath, local-source)
subdirectory = $(patsubst %/module.mk,%, \
	$(word \
	$(words $(MAKEFILE_LIST)),$(MAKEFILE_LIST)))
changepath = $(addprefix $(subdirectory)/,$(1))

include $(addsuffix /module.mk,$(modules))
ifneq "$(MAKECMDGOALS)" "clean"
_MKDIRS := $(shell mkdir $(BIN_DIR) 2>/dev/null)
_MKDIRS := $(shell for d in $(modules); \
	do \
		mkdir -p $(BIN_DIR)$$d; \
	done)
endif

########################### rules ############################################
.PHONY: begin end all clean sizebefore sizeafter build elf hex bin lss sym clean \
	clean_list
	
# Default target.
all: begin sizebefore $(prebuild) build $(postbuild) sizeafter end

# Target: clean project.
clean: begin clean_list end

# build target
ifeq ($(FORMAT),ihex)
build: elf hex lss sym
hex: $(PROJECT).hex
IMGEXT=hex
else
ifeq ($(FORMAT),binary)
build: elf bin lss sym
bin: $(PROJECT).bin
IMGEXT=bin
else
$(error "Can not handle output-format $(FORMAT)")
endif
endif

elf: $(PROJECT).elf
lss: $(PROJECT).lss
sym: $(PROJECT).sym

#make ELF
%.elf: $(objects)
	@echo
	@echo Linking: $@
	$(CC) $(GCCFLAGS) $(objects) --output $@ $(LDFLAGS)
	
# Create final output file (.hex) from ELF output file.
%.hex: %.elf
	@echo
	@echo Creating load file for Flash: $@
	$(OBJCOPY) -O $(FORMAT) $< $@
	
# Create final output file (.bin) from ELF output file.
%.bin: %.elf
	@echo
	@echo Creating load file for Flash: $@
	$(OBJCOPY) -O $(FORMAT) $< $@
	#cp $@ $(TFTP_PATH)$(@F)
	
# Create extended listing file from ELF output file.
# testing: option -C
%.lss: %.elf
	@echo
	@echo Creating Extended Listing: $@
	$(OBJDUMP) -h -S -C $< > $@
	
# Create a symbol table from ELF output file.
%.sym: %.elf
	@echo
	@echo Creating Symbol Table: $@
	$(NM) -n $< > $@
	
clean_list :
	@echo
	@echo Cleaning project:
	$(REMOVE) $(BIN_DIR)

begin:
	@echo
	@echo "-------- begin (make $(MAKECMDGOALS)) --------"
	@echo
	@$(AS) --version
	@echo
	@$(LD) --version
	@echo
	@$(CC) --version
	@echo
end:
	@echo "-------- end --------"
	
# Display size of file.
sizebefore:
	@if [ -f $(PROJECT).elf ]; then echo; echo Size before:; $(ELFSIZE); echo; fi
sizeafter:
	@if [ -f $(PROJECT).elf ]; then echo; echo Size after:; $(ELFSIZE); echo; fi
	
# Assemble: create object files from assembler source files.
$(aobjects) : $(BIN_DIR)%.o : %.s
	@echo
	@echo Assembling: $<
	$(CC) -c $(GCCFLAGS) $(ASFLAGS) $(GENDEPFLAGS) $< -o $@
	# $(OBJDUMP) -h $@

# Compile: create object files from C source files.
$(cobjects) : $(BIN_DIR)%.o : %.c
	@echo
	@echo Compiling C: $<
	$(CC) -c $(GCCFLAGS) $(CFLAGS) $(CONLYFLAGS) $(GENDEPFLAGS) $< -o $@
	# $(OBJDUMP) -h $@
	
# Don't try to MAKE the following extentions:
%.dep %.mk %.c %.h %.s:
	@echo make will ignore this target $@
	@echo
	
# Include the dependency files.
ifneq "$(MAKECMDGOALS)" "clean"
-include $(dependencies)
endif
