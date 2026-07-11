### Thank you to ds-pokemon-hacking/ESDB-Tools!

esdb: $(pmc_dir)/$(rom_code).yml

# Misc. vars
venv := $(build_dir)/venv
reqs := pyyaml

# -------------------------------------------------------------------
# Rules
# -------------------------------------------------------------------
# ESDBs
## Trims and outputs the final ESDB
$(pmc_dir)/%.yml: $(incl_dir)/swan/%.yml $(srcs) $(venv)
	@ echo "[-] Trimming the final ESDB..."
	@ source "$(venv)/bin/activate"; \
	  $(python) $(ESDBTrim) -i $< -i ghidra.yml -o $@ $(addprefix -s, $(srcs))

# Creates the venv if necessary
$(venv):
	@ echo "[#] Creating Python virtual environment..."
	@ $(python) -m venv $(venv)
	@ echo "[^] Installing PyYAML..."
	@ source "$(venv)/bin/activate"; \
	  $(python) -m pip install $(reqs) > /dev/null
