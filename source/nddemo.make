
# ---------------------------------------------------------------------------- #

################################################################################
#
# PROJECT
#
################################################################################

# this is the project's name. should be a filesystem-safe name.
PROJECT = nddemo

# this is the project's output filename, including extension.
TARGET = $(PROJECT)$(ELF_SUFFIX)

# you can change any paths here if you don't want the default behavior.
SRC_PATH = $(SRC_ROOT)
BIN_PATH = $(BIN_ROOT)
DEP_PATH = $(DEP_ROOT)
OBJ_PATH = $(OBJ_ROOT)

# add any libraries to link here (used only if project is an executable)
LIBS = \
	$(MW_LIBS) \
	$(SDK_LIBS)

################################################################################
#
# SOURCES
#
################################################################################

AS_SRCS =

# ---------------------------------------------------------------------------- #

C_SRCS =

# ---------------------------------------------------------------------------- #

CXX_SRCS = \
	main.cpp \
	DTPad.cpp

################################################################################
#
# BUILD RULES
#
################################################################################

include $(ROOT_PATH)/project.make

# ---------------------------------------------------------------------------- #
