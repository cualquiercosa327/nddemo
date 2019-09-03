
# ---------------------------------------------------------------------------- #

empty:=
space:= $(empty) $(empty)

# ---------------------------------------------------------------------------- #

# FIXME some unknown 'rv' flag is being passed here externally -- remove it
ARFLAGS =

################################################################################
#
# CONFIGURATIONS & PLATFORMS
#
################################################################################

CONFIGURATIONS := DEBUG RELEASE
CONFIGURATION ?= RELEASE

PLATFORMS := HW1 HW2
PLATFORM ?= HW2

# ---------------------------------------------------------------------------- #

ifeq ($(CONFIGURATION), DEBUG)
CONFIGURATION = DEBUG
DEBUG         = TRUE
ASFLAGS      += -D_DEBUG
CCFLAGS      += -D_DEBUG
CXXFLAGS     += -D_DEBUG
else ifeq ($(CONFIGURATION), RELEASE)
CONFIGURATION = RELEASE
DEBUG         = FALSE
ASFLAGS      += -DNDEBUG
CCFLAGS      += -DNDEBUG
CXXFLAGS     += -DNDEBUG
else
$(error Unknown configuration '$(CONFIGURATION)'. Must be one of: $(CONFIGURATIONS))
endif

# ---------------------------------------------------------------------------- #

ifeq ($(PLATFORM), HW2)
EPPC            = TRUE
MARLIN          = DI
ORCA            = TRUE
PROCESSOR       = gekko
TRK_INTEGRATION = TRUE
GX_REV          = 2
BUGLIST        += BUG_CLR_LOAD_DLY
BUGLIST        += BUG_XF_STALL
else ifeq ($(PLATFORM), HW1)
EPPC            = TRUE
MARLIN          = DI
ORCA            = TRUE
PROCESSOR       = gekko
TRK_INTEGRATION = TRUE
GX_REV          = 1
BUGLIST        += BUG_BYPASS_REG
BUGLIST        += BUG_INDX_ALIGN
BUGLIST        += BUG_TRIANGLE_FAN
BUGLIST        += BUG_NO_8b_SCALE
BUGLIST        += BUG_INDX_MTX_LOAD
BUGLIST        += BUG_MTX_INDX_VTX
BUGLIST        += BUG_DBL_CLR_LOAD
BUGLIST        += BUG_16MB_XFB_LMT
BUGLIST        += BUG_XF_STALL
else
$(error Unknown platform '$(PLATFORM)'. Must be one of: $(PLATFORMS))
endif

# ---------------------------------------------------------------------------- #

ifdef EPPC
ASFLAGS  += -DEPPC
CCFLAGS  += -DEPPC
CXXFLAGS += -DEPPC
endif

# ---------------------------------------------------------------------------- #

ifdef MARLIN
ASFLAGS  += -DMARLIN=$(MARLIN)
CCFLAGS  += -DMARLIN=$(MARLIN)
CXXFLAGS += -DMARLIN=$(MARLIN)
endif

# ---------------------------------------------------------------------------- #

ifdef ORCA
ASFLAGS  += -DORCA
CCFLAGS  += -DORCA
CXXFLAGS += -DORCA
endif

# ---------------------------------------------------------------------------- #

ifeq ($(PROCESSOR), gekko)
GEKKO     = TRUE
ASFLAGS  += -DGEKKO
CCFLAGS  += -DGEKKO
CXXFLAGS += -DGEKKO
endif

# ---------------------------------------------------------------------------- #

ifdef GX_REV
ASFLAGS  += -DGX_REV=$(GX_REV)
CCFLAGS  += -DGX_REV=$(GX_REV)
CXXFLAGS += -DGX_REV=$(GX_REV)
endif

# ---------------------------------------------------------------------------- #

ifeq ($(CONFIGURATION), DEBUG)
ASFLAGS  += -g
CCFLAGS  += -g
CXXFLAGS += -g
LDFLAGS  += -g
endif

# ---------------------------------------------------------------------------- #

BUGFLAGS  = $(addprefix -D, $(BUGLIST))
ASFLAGS  += $(BUGFLAGS)
CCFLAGS  += $(BUGFLAGS)
CXXFLAGS += $(BUGFLAGS)

# ---------------------------------------------------------------------------- #

LIB_SUFFIX    := .a
ELF_SUFFIX    := .elf
DOL_SUFFIX    := .dol
PLF_SUFFIX    := .plf
PREPLF_SUFFIX := .preplf
REL_SUFFIX    := .rel
STR_SUFFIX    := .str
LCF_SUFFIX    := .lcf
LST_SUFFIX    := .lst
MAP_SUFFIX    := .map

ifeq ($(CONFIGURATION), DEBUG)
LIB_SUFFIX    := $(addprefix D,$(LIB_SUFFIX))
ELF_SUFFIX    := $(addprefix D,$(ELF_SUFFIX))
DOL_SUFFIX    := $(addprefix D,$(DOL_SUFFIX))
PLF_SUFFIX    := $(addprefix D,$(PLF_SUFFIX))
PREPLF_SUFFIX := $(addprefix D,$(PREPLF_SUFFIX))
REL_SUFFIX    := $(addprefix D,$(REL_SUFFIX))
STR_SUFFIX    := $(addprefix D,$(STR_SUFFIX))
LCF_SUFFIX    := $(addprefix D,$(LCF_SUFFIX))
LST_SUFFIX    := $(addprefix D,$(LST_SUFFIX))
MAP_SUFFIX    := $(addprefix D,$(MAP_SUFFIX))
endif

DEP_SUFFIX := .d
OBJ_SUFFIX := .o

# ---------------------------------------------------------------------------- #

ASFLAGS += -nodefaults -proc $(PROCESSOR) -D$(PLATFORM)
LDFLAGS += -nodefaults -fp hardware -unused -map ${@:$(ELF_SUFFIX)=$(MAP_SUFFIX)} -lcf linker.lcf
ARFLAGS += -nodefaults -xm l

CCFLAGS += \
	-nodefaults -proc $(PROCESSOR) -D$(PLATFORM) \
	-align powerpc -enum int -multibyte -MMD -rtti off \
	-char unsigned -fp hardware -Cpp_exceptions off

CXXFLAGS += \
	-nodefaults -proc $(PROCESSOR) -D$(PLATFORM) \
	-align powerpc -enum int -multibyte -MMD -rtti off \
	-char unsigned -fp hardware -Cpp_exceptions off

################################################################################
#
# WARNINGS & OPTIMIZATIONS
#
################################################################################

WARNINGS = \
	-w all, \
	nonotused, \
	noimplicit, \
	nounusedarg, \
	nonotinlined

CCFLAGS += $(WARNINGS)
CXXFLAGS += $(WARNINGS)

# ---------------------------------------------------------------------------- #

ifeq ($(CONFIGURATION), DEBUG)
OPTIMIZATIONS = \
	-opt off \
	-inline off
else
OPTIMIZATIONS = \
	-opt level=2, peephole \
	-inline off, auto
endif

CCFLAGS += $(OPTIMIZATIONS)
CXXFLAGS += $(OPTIMIZATIONS)

################################################################################
#
# GLOBAL PATHS
#
################################################################################

ROOT_PATH := $(realpath .)
SRC_ROOT := $(ROOT_PATH)/source

# ---------------------------------------------------------------------------- #

ifdef DOLPHIN_ROOT
SDK_PATH := $(subst $(space),\$(space),$(subst \,/,$(DOLPHIN_ROOT)))
else
SDK_PATH := /dolphin
endif

SDK_LIB_PATH := $(SDK_PATH)/$(PLATFORM)/lib

# ---------------------------------------------------------------------------- #

ifdef MUSYX_ROOT
MUSYX_PATH := $(subst $(space),\$(space),$(subst \,/,$(MUSYX_ROOT)))
else
MUSYX_PATH := /MusyXSDK
endif

# ---------------------------------------------------------------------------- #

ifdef HVQ_ROOT
HVQ_PATH := $(subst $(space),\$(space),$(subst \,/,$(HVQ_ROOT)))
else
HVQ_PATH := /HVQM4
endif

# ---------------------------------------------------------------------------- #

MW_CW_PATH     := $(subst $(space),\$(space),$(subst \,/,$(CWFOLDER)))
AMC_DDK_PATH   := $(subst $(space),\$(space),$(subst \,/,$(AMCDDKBIN)))
ODEMU_SDK_PATH := $(subst $(space),\$(space),$(subst \,/,$(ODEMUSDKBIN)))

MW_BIN_PATH := $(MW_CW_PATH)/PowerPC_EABI_TOOLS/Command_Line_Tools
MW_LIB_PATH := $(MW_CW_PATH)/PowerPC_EABI_Support

# ---------------------------------------------------------------------------- #

BUILD_ROOT := $(ROOT_PATH)/build/$(CONFIGURATION)-$(PLATFORM)
BIN_ROOT   := $(BUILD_ROOT)/bin
DEP_ROOT   := $(BUILD_ROOT)/dep
OBJ_ROOT   := $(BUILD_ROOT)/obj

# ---------------------------------------------------------------------------- #

AS  := $(MW_BIN_PATH)/mwasmeppc.exe
CC  := $(MW_BIN_PATH)/mwcceppc.exe
CXX := $(MW_BIN_PATH)/mwcceppc.exe
LD  := $(MW_BIN_PATH)/mwldeppc.exe
AR  := $(MW_BIN_PATH)/mwldeppc.exe

################################################################################
#
# LIBRARIES
#
################################################################################

# dolphin sdk
LDFLAGS += -lr $(SDK_LIB_PATH)

# metroworks
LDFLAGS += -lr $(MW_LIB_PATH)

# project libraries
LDFLAGS += -lr $(BIN_ROOT)

# ---------------------------------------------------------------------------- #

MW_LIBS = \
	Runtime.PPCEABI.H.a \
	MSL_C.PPCEABI.bare.H.a

ifdef TRK_INTEGRATION
CCFLAGS  += -DTRK_INTEGRATION
CXXFLAGS += -DTRK_INTEGRATION
MW_LIBS += TRK_MINNOW_DOLPHIN.a

ifdef ODEMUSDKBIN
LDFLAGS += -L$(realpath $(ODEMU_SDK_PATH)/../lib)
TRK_LIBS += OdemuExi2.a
endif

ifdef AMCDDKBIN
LDFLAGS += -L$(realpath $(AMC_DDK_PATH)/../lib)
TRK_LIBS += AmcExi2.a
endif

ifdef AMCDDKBIN
TRK_LIBS += amcnotstub$(LIB_SUFFIX)
else
TRK_LIBS += amcstubs$(LIB_SUFFIX)
endif

ifdef ODEMUSDKBIN
TRK_LIBS += odenotstub$(LIB_SUFFIX)
else
TRK_LIBS += odemustubs$(LIB_SUFFIX)
endif

endif

# ---------------------------------------------------------------------------- #

SDK_LIBS = \
	base$(LIB_SUFFIX) \
	db$(LIB_SUFFIX) \
	os$(LIB_SUFFIX) \
	mtx$(LIB_SUFFIX) \
	dvd$(LIB_SUFFIX) \
	vi$(LIB_SUFFIX) \
	pad$(LIB_SUFFIX) \
	ai$(LIB_SUFFIX) \
	ar$(LIB_SUFFIX) \
	dsp$(LIB_SUFFIX) \
	card$(LIB_SUFFIX) \
	gx$(LIB_SUFFIX) \
	$(TRK_LIBS) \
	gd$(LIB_SUFFIX) \
	si$(LIB_SUFFIX) \
	exi$(LIB_SUFFIX)

################################################################################
#
# INCLUDES
#
################################################################################

SYSTEM_INCLUDES = \
	-I$(SDK_PATH)/include \
	-ir $(MW_CW_PATH)/PowerPC_EABI_Support/MSL/MSL_C \
	-ir $(MW_CW_PATH)/PowerPC_EABI_Support/MSL/MSL_C++ \
	-I$(MW_CW_PATH)/PowerPC_EABI_Support/Runtime/Inc

# ---------------------------------------------------------------------------- #

USER_INCLUDES = \
	-I$(SRC_ROOT)

# ---------------------------------------------------------------------------- #

INCLUDES = $(USER_INCLUDES) -i- $(SYSTEM_INCLUDES)

# ---------------------------------------------------------------------------- #

CCFLAGS += -nosyspath
CXXFLAGS += -nosyspath

################################################################################
#
# PROJECTS
#
################################################################################

PROJECTS = \
	nddemo

# ---------------------------------------------------------------------------- #

# this rule should always be the first so as to be default
build: $(PROJECTS)

clean:
	@echo Cleaning build directories...
	@rm -rf $(BIN_ROOT)
	@rm -rf $(DEP_ROOT)
	@rm -rf $(OBJ_ROOT)
	@echo Done.

# ---------------------------------------------------------------------------- #

include $(addprefix $(SRC_ROOT)/, $(addsuffix .make,$(PROJECTS)))

# ---------------------------------------------------------------------------- #
