HOSTNAME = $(shell hostname)

ifeq ($(HOSTNAME), ydmdtn001)
	GCC_PATH = C:/gcc-arm-none-eabi-9-2019-q4-major-win32/bin
endif
ifeq ($(HOSTNAME), ydmnts019)
	GCC_PATH = $(subst \,/,$(ARM_NONE_EABI_TOOLS_DIR))
endif
ifeq ($(HOSTNAME), MacBookAir)
	GCC_PATH = $(subst \,/,$(ARM_NONE_EABI_TOOLS_DIR))
endif