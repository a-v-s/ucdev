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

BUILD_MODE?=DEBUG

ifeq ($(COMPILER_TYPE), GCC)
	ifeq ($(BUILD_MODE), DEBUG)
		OPT ?= -O0 -g3
	endif

	ifeq ($(BUILD_MODE), RELEASE_SIZE)
		OPT ?= -Os
	endif

	ifeq ($(BUILD_MODE), RELEASE_SPEED)
		OPT ?= -O2
	endif
endif 



ifeq ($(COMPILER_TYPE), SDCC)
	ifeq ($(BUILD_MODE), DEBUG)
		OPT ?= 
	endif

	ifeq ($(BUILD_MODE), RELEASE_SIZE)
		OPT ?= --opt-code-size
	endif

	ifeq ($(BUILD_MODE), RELEASE_SPEED)
		OPT ?= --opt-code-speed
	endif
endif 



$(info DEBUG: BUILD_MODE IN OPT 	   $(BUILD_MODE))
$(info DEBUG: OPT IN OPT 	   		   $(OPT))
