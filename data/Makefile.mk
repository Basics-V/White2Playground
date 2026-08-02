### This file references ds-pokemon-hacking/White2Upgrade
### A huge thank you to the contributors of ds-pokemon-hacking
### for all of their hard work over the years!

# General file system definition
build_fs     := $(build_dir)/romfs/data
W2Playground := $(build_fs)/White2Playground

# -------------------------------------------------------------------
# ARC Definitions
# -------------------------------------------------------------------
# ARC labels
TEXT_SYSTEM_ARC        := a/0/0/2
TEXT_EVENTS_ARC        := a/0/0/3

# -------------------------------------------------------------------
# Data Directories
# -------------------------------------------------------------------
# General ARCs
TEXT_SYSTEM_ROOT     := $(data_dir)/text/system
TEXT_EVENTS_ROOT     := $(data_dir)/text/events
FIELD_SCRIPT_ROOT    := $(data_dir)/scripting/scripts
GENERAL_ROOT         := $(data_dir)

# -------------------------------------------------------------------
# Targets 
# -------------------------------------------------------------------
# Generic
TEXT_SYSTEM_FILES := $(patsubst $(TEXT_SYSTEM_ROOT)/%.txt, $(build_fs)/$(TEXT_SYSTEM_ARC)/%, $(wildcard $(TEXT_SYSTEM_ROOT)/*))
TEXT_EVENTS_FILES := $(patsubst $(TEXT_EVENTS_ROOT)/%.txt, $(build_fs)/$(TEXT_EVENTS_ARC)/%, $(wildcard $(TEXT_EVENTS_ROOT)/*))
SCRIPT_FILES      := $(patsubst $(FIELD_SCRIPT_ROOT)/%.pks, $(W2Playground)/%.ev, $(wildcard $(FIELD_SCRIPT_ROOT)/*))
ROOT_FILES        := $(wildcard $(GENERAL_ROOT)/*.bin)

# PKS Base and Extension(s)
SCRIPT_LIB   := ctrmap/resources/scripting/cm_ide/sdk/EV_GEN_V/SDK5-B2W2-Generated.lib
PKS_INCLUDE  := $(build_dir)/.temp.lib

# Final
data: $(build_fs) $(W2Playground) $(build_fs)/$(TEXT_SYSTEM_ARC) $(build_fs)/$(TEXT_EVENTS_ARC) $(SCRIPT_FILES)

# -------------------------------------------------------------------
# Rules
# -------------------------------------------------------------------
# Root files
## Fills the root.
$(W2Playground): $(ROOT_FILES)
	@ for file in $^; do \
	    echo "[+] Storing $$file..."; \
		mkdir -p $@; \
		cp $$file $@; \
	  done

# All unstructured NARCs
$(build_fs): $(data_dir)/a
	@ echo "[+] Storing all unstructured NARCs..."
	@ mkdir -p $@
	@ cp -R $< $@

# Text System ARC
## Builds the ARC.
$(build_fs)/$(TEXT_SYSTEM_ARC): $(TEXT_SYSTEM_FILES)
## Builds the files in the ARC.
$(build_fs)/$(TEXT_SYSTEM_ARC)/%: $(TEXT_SYSTEM_ROOT)/%.txt
	@ echo "[+] Encoding $^..."
	@ mkdir -p $(dir $@)
	@ java -cp $(CTRMapV):$(CTRMap) ctrmap.util.tools.TextUtil -t bin -a system -i $^ -o $@

# Text Events ARC
## Builds the ARC.
$(build_fs)/$(TEXT_EVENTS_ARC): $(TEXT_EVENTS_FILES)
## Builds the files in the ARC.
$(build_fs)/$(TEXT_EVENTS_ARC)/%: $(TEXT_EVENTS_ROOT)/%.txt
	@ echo "[+] Encoding $^..."
	@ mkdir -p $(dir $@)
	@ java -cp $(CTRMapV):$(CTRMap) ctrmap.util.tools.TextUtil -t bin -a script -i $^ -o $@

# Field Script ARC
## Builds the files in the ARC.
$(W2Playground)/%.ev: $(FIELD_SCRIPT_ROOT)/%.pks
	@ echo "[+] Compiling $<..."
	@ mkdir -p $(dir $@)
	@ unzip -p $(CTRMapV) $(SCRIPT_LIB) > $(build_dir)/.temp.lib
	@ logfile="$(build_dir)/$(basename $(notdir $<))"; \
	  java -cp $(CTRMap) ctrmap.pokescript.LangCompiler -t ntrv -i $< -o $@ -I $(PKS_INCLUDE) -l $$logfile.log > $$logfile.out
	@ rm -f $(build_dir)/.temp.lib
