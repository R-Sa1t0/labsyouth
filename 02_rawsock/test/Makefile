# Makefile

VENV_PATH ?=
REQUIRED_PACKAGES = scapy pyroute2

.PHONY: all check_venv_path setup_venv enter_venv

all: check_python_version check_venv_path setup_venv check_venv install_required_packages

check_python_version:
	@python3 -c 'import sys; sys.exit(not (sys.version_info.major == 3 and sys.version_info.minor >= 11))' || { \
	    echo "Python 3.11 or higher is required"; \
	    exit 1; \
	}

check_venv_path:
	@if [ -z "$(VENV_PATH)" ]; then \
	    echo "VENV_PATH is not set"; \
	    exit 1; \
	fi

setup_venv:
	@if [ -z "$(shell ls -A $(VENV_PATH) 2>/dev/null)" ]; then \
	    echo "VENV_PATH is empty. Creating a new venv at $(VENV_PATH)."; \
	    python3 -m venv $(VENV_PATH); \
	fi

check_venv:
	@if [ -d "$(VENV_PATH)/bin" ]; then \
	    echo "venv path: $(VENV_PATH)"; \
	    . $(VENV_PATH)/bin/activate; \
	    echo "venv ok."; \
	else \
	    echo "$(VENV_PATH) is not a valid venv"; \
	    exit 1; \
	fi

enter_venv:
	@echo "venv activating: $(VENV_PATH)"; \
	. $(VENV_PATH)/bin/activate && which python3;

install_required_packages: enter_venv
	@echo "Installing packages: $(REQUIRED_PACKAGES)"; \
	which python3
	
