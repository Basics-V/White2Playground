### Thank you to ds-pokemon-hacking/ESDB-Tools!

esdb: $(pmc_dir)/$(rom_code).yml

# Misc. vars
venv     := $(build_dir)/venv
reqs     := pyyaml
ext_esdb := $(wildcard $(incl_dir)/*.yml)
ext_idb  := $(wildcard $(incl_dir)/*.idb)
idb_esdb := $(addprefix $(build_dir)/idb/, $(notdir $(ext_idb:.idb=.yml)))

# -------------------------------------------------------------------
# Rules
# -------------------------------------------------------------------
# ESDBs
## Trims and outputs the final ESDB
$(pmc_dir)/%.yml: $(incl_dir)/swan/%.yml $(srcs) $(venv) $(ext_esdb) $(idb_esdb)
	@ echo "[-] Trimming the final ESDB..."
	@ source "$(venv)/bin/activate"; \
	  $(python) $(ESDBTrim) -i $< $(addprefix -i , $(ext_esdb)) $(addprefix -i , $(idb_esdb)) -o $@ $(addprefix -s , $(srcs))

# Build the extra ESDBs from the supplied IDBs
.PRECIOUS: $(build_dir)/idb/%.yml
$(build_dir)/idb/%.yml: $(incl_dir)/%.idb $(venv)
	@ echo "[$$] Extracting symbols from $<..."
	@ mkdir -p $(@D)
	@ source "$(venv)/bin/activate"; \
	  ($(python) $(IDBTool) $< --segs; $(python) $(IDBTool) $< -n) | $(python) $(IDBCurate) > $@

# Creates the venv if necessary
$(venv):
	@ echo "[#] Creating Python virtual environment..."
	@ $(python) -m venv $(venv)
	@ echo "[^] Installing requirements..."
	@ source "$(venv)/bin/activate"; \
	  $(python) -m pip install $(reqs) > /dev/null
