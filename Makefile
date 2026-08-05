### This file heavily references ds-pokemon-hacking/White2Upgrade
### A huge thank you to the contributors of ds-pokemon-hacking
### for all of their hard work over the years!

# Project specific
project         := White2Playground
rom_code        := IRDO

# Directory configuration
build_dir        = build
incl_dir        := include

romfs           := $(build_dir)/romfs
build_fs        := $(romfs)/data

src_dir          = src
data_dir        := data
pmc_dir         := pmc
patches_dir     := $(build_fs)/patches

# Targets
## Code
asm_src         := $(wildcard $(src_dir)/*.s)
asm_obj         := $(addprefix $(build_dir)/code/, $(notdir $(asm_src:.s=_s.o)))
c_src           := $(wildcard $(src_dir)/*.c)
c_obj           := $(addprefix $(build_dir)/code/, $(notdir $(c_src:.c=_c.o)))
cpp_src         := $(wildcard $(src_dir)/*.cpp)
cpp_obj         := $(addprefix $(build_dir)/code/, $(notdir $(cpp_src:.cpp=_cpp.o)))
headers         := $(wildcard $(incl_dir)/*.h)
srcs            := $(asm_src) $(c_src) $(cpp_src)
objs            := $(asm_obj) $(c_obj) $(cpp_obj)
esdb            := $(pmc_dir)/$(rom_code).yml

# Tools
as              := arm-none-eabi-as
gcc             := arm-none-eabi-gcc
ld              := arm-none-eabi-ld
python          := python3
CTRMap          := tools/CTRMap.jar
CTRMapV         := tools/CTRMapV.jar
ESDBTrim        := tools/ESDBTrimmer.py
IDBTool         := tools/pyidbutil/idbtool.py
IDBCurate       := tools/IDBCurator.py

# Flags
as_flags        := -mthumb -march=armv5t -r -W -x assembler-with-cpp
c_flags         := -mthumb -march=armv5t -r -w
mods            ?= # Example usage: make mods="PHENOM_RAND_MAN SKIP_INTRO_MOVIE"
def_flags       := $(mods)
include_flags   := -I$(incl_dir) -I$(incl_dir)/swan -I$(incl_dir)/PW2Code

# Debug mode
debug ?= none
ifneq ($(debug), none)
    def_flags += DEBUG

	# Platform-specific
	ifeq ($(debug), desmume)
		def_flags += DESMUME
	else ifeq ($(debug), melonds)
		def_flags += MELONDS
	endif
endif

# Add the mod flags
as_flags += $(addprefix -D, $(def_flags))
c_flags  += $(addprefix -D, $(def_flags))

# Add our includes
c_flags  += $(include_flags)
as_flags += $(include_flags)

vpath %.s   $(src_dir)
vpath %.c   $(src_dir)
vpath %.cpp $(src_dir)

# -------------------------------------------------------------------
# Targets 
# -------------------------------------------------------------------
# Default
all: code

# Code
code: $(patches_dir)/$(project).dll

$(patches_dir)/%.dll: $(build_dir)/%.elf
	@ mkdir -p $(@D)
	@ echo "[>] Creating DLL $@..."
	@ java -cp $(CTRMap) rpm.cli.RPMTool -i $< --fourcc DLXF -o $@ --esdb $(esdb) --generate-relocations > /dev/null

$(build_dir)/%.elf: $(objs) $(build_data)
	@ echo "[+] Linking all objects into $@..."
	@ $(ld) -o $@ -r $^

# -------------------------------------------------------------------
# Prerequisites 
# -------------------------------------------------------------------
# All code compilation/assembly rules
$(build_dir)/code/%_s.o: %.s
	@ echo "[+] Assembling $<..."
	@ mkdir -p $(@D)
	@ $(gcc) $(as_flags) -c $< -o $@

$(build_dir)/code/%_c.o: %.c $(headers)
	@ echo "[+] Compiling $<..."
	@ mkdir -p $(@D)
	@ $(gcc) $(c_flags) -c $< -o $@

$(build_dir)/code/%_cpp.o: %.cpp $(headers)
	@ echo "[+] Compiling $<..."
	@ mkdir -p $(@D)
	@ $(gcc) $(c_flags) -c $< -o $@

# Include the Makefile for our ESDB's rules
include $(pmc_dir)/Makefile.mk

# Include the Makefile for our data structures
include $(data_dir)/Makefile.mk

# Clean the working directory
clean:
	rm -rf $(build_dir)

.PHONY: all code esdb clean
