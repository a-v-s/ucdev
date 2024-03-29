BUILD_MODE?=DEBUG

ifeq (1,$(DEBUG))
	BUILD_MODE=DEBUG
endif

ifeq (1,$(RELEASE))
	BUILD_MODE=RELEASE_SIZE
endif

ifeq (1,$(RELEASE_SIZE))
	BUILD_MODE=RELEASE_SIZE
endif

ifeq (1,$(RELEASE_SPEED))
	BUILD_MODE=RELEASE_SPEED
endif



ifeq ($(COMPILER_TYPE), GCC)
	ifeq ($(BUILD_MODE), DEBUG)
		OPT ?= -O0 -g3
		CFLAGS += -DDEBUG
	endif

	ifeq ($(BUILD_MODE), RELEASE_SIZE)
		OPT ?= -Os
		CFLAGS += -DRELEASE
	endif

	ifeq ($(BUILD_MODE), RELEASE_SPEED)
		OPT ?= -O2
		CFLAGS += -DRELEASE
	endif
endif 



ifeq ($(COMPILER_TYPE), SDCC)
	ifeq ($(BUILD_MODE), DEBUG)
		# TODO What flags are required for an SDCC debug build?
		OPT ?= 
		CFLAGS += -DDEBUG
	endif

	ifeq ($(BUILD_MODE), RELEASE_SIZE)
		OPT ?= --opt-code-size
		CFLAGS += -DRELEASE
	endif

	ifeq ($(BUILD_MODE), RELEASE_SPEED)
		OPT ?= --opt-code-speed
		CFLAGS += -DRELEASE
	endif
endif 



$(info BUILD_MODE    $(BUILD_MODE))
#$(info DEBUG: OPT IN OPT 	   		   $(OPT))
